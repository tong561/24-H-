#include "MPU6050.h"
#include "IIC.h"
//#include "sys.h"
//#include <math.h>
#include <ti/iqmath/include/IQmathLib.h>
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "usart.h"
#include "stdio.h"
#include "motor.h"
#define PRINT_ACCEL     (0x01)
#define PRINT_GYRO      (0x02)
#define PRINT_QUAT      (0x04)
#define ACCEL_ON        (0x01)
#define GYRO_ON         (0x02)
#define MOTION          (0)
#define NO_MOTION       (1)
#define DEFAULT_MPU_HZ  (200)
#define FLASH_SIZE      (512)
#define FLASH_MEM_START ((void*)0x1800)
	
#define q30  1073741824.0f//q30∏Ò Ω

short gyro[3], accel[3], sensors;
//float Pitch,Roll; 

static signed char gyro_orientation[9] = {-1, 0, 0,//◊™ªØæÿ’Û
                                           0,-1, 0,
                                           0, 0, 1};

static  unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}


static  unsigned short inv_orientation_matrix_to_scalar(
    const signed char *mtx)
{
    unsigned short scalar;
    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;


    return scalar;
}

static void run_self_test(void)
{
    int result;
    long gyro[3], accel[3];

    result = mpu_run_self_test(gyro, accel);
    if (result == 0x7) {
        /* Test passed. We can trust the gyro data here, so let's push it down
         * to the DMP.
         */
        float sens;
        unsigned short accel_sens;
        mpu_get_gyro_sens(&sens); //ªÒ»°gyro¡È√Ù∂»
        gyro[0] = (long)(gyro[0] * sens);
        gyro[1] = (long)(gyro[1] * sens);
        gyro[2] = (long)(gyro[2] * sens);
        dmp_set_gyro_bias(gyro);
        mpu_get_accel_sens(&accel_sens);
        accel[0] *= accel_sens;
        accel[1] *= accel_sens;
        accel[2] *= accel_sens;
        dmp_set_accel_bias(accel);
		printf("setting bias succesfully ......\r\n");
    }
}



uint8_t buffer[14];

int16_t  MPU6050_FIFO[6][11];
int16_t Gx_offset=0,Gy_offset=0,Gz_offset=0;


/************************** µœ÷∫Ø ˝********************************************
*∫Ø ˝‘≠–Õ:		void  MPU6050_newValues(int16_t ax,int16_t ay,int16_t az,int16_t gx,int16_t gy,int16_t gz)
*π¶°°°°ƒ‹:	    Ω´–¬µƒADC ˝æ›∏¸–¬µΩ FIFO ˝◊È£¨Ω¯––¬À≤®¥¶¿Ì
*******************************************************************************/

void  MPU6050_newValues(int16_t ax,int16_t ay,int16_t az,int16_t gx,int16_t gy,int16_t gz)
{
unsigned char i ;
int32_t sum=0;
for(i=1;i<10;i++){	//FIFO ≤Ÿ◊˜
MPU6050_FIFO[0][i-1]=MPU6050_FIFO[0][i];
MPU6050_FIFO[1][i-1]=MPU6050_FIFO[1][i];
MPU6050_FIFO[2][i-1]=MPU6050_FIFO[2][i];
MPU6050_FIFO[3][i-1]=MPU6050_FIFO[3][i];
MPU6050_FIFO[4][i-1]=MPU6050_FIFO[4][i];
MPU6050_FIFO[5][i-1]=MPU6050_FIFO[5][i];
}
MPU6050_FIFO[0][9]=ax;//Ω´–¬µƒ ˝æ›∑≈÷√µΩ  ˝æ›µƒ◊Ó∫Û√Ê
MPU6050_FIFO[1][9]=ay;
MPU6050_FIFO[2][9]=az;
MPU6050_FIFO[3][9]=gx;
MPU6050_FIFO[4][9]=gy;
MPU6050_FIFO[5][9]=gz;

sum=0;
for(i=0;i<10;i++){	//«Ûµ±«∞ ˝◊Èµƒ∫œ£¨‘Ÿ»°∆Ωæ˘÷µ
   sum+=MPU6050_FIFO[0][i];
}
MPU6050_FIFO[0][10]=sum/10;

sum=0;
for(i=0;i<10;i++){
   sum+=MPU6050_FIFO[1][i];
}
MPU6050_FIFO[1][10]=sum/10;

sum=0;
for(i=0;i<10;i++){
   sum+=MPU6050_FIFO[2][i];
}
MPU6050_FIFO[2][10]=sum/10;

sum=0;
for(i=0;i<10;i++){
   sum+=MPU6050_FIFO[3][i];
}
MPU6050_FIFO[3][10]=sum/10;

sum=0;
for(i=0;i<10;i++){
   sum+=MPU6050_FIFO[4][i];
}
MPU6050_FIFO[4][10]=sum/10;

sum=0;
for(i=0;i<10;i++){
   sum+=MPU6050_FIFO[5][i];
}
MPU6050_FIFO[5][10]=sum/10;
}



/************************** µœ÷∫Ø ˝********************************************
*∫Ø ˝‘≠–Õ:		void MPU6050_setClockSource(uint8_t source)
*π¶°°°°ƒ‹:	    …Ë÷√  MPU6050 µƒ ±÷”‘¥
 * CLK_SEL | Clock Source
 * --------+--------------------------------------
 * 0       | Internal oscillator
 * 1       | PLL with X Gyro reference
 * 2       | PLL with Y Gyro reference
 * 3       | PLL with Z Gyro reference
 * 4       | PLL with external 32.768kHz reference
 * 5       | PLL with external 19.2MHz reference
 * 6       | Reserved
 * 7       | Stops the clock and keeps the timing generator in reset
*******************************************************************************/
void MPU6050_setClockSource(uint8_t source){
	
		//MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1,0x00+source);
    IICwriteBits(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);

}

/** Set full-scale gyroscope range.
 * @param range New full-scale gyroscope range value
 * @see getFullScaleRange()
 * @see MPU6050_GYRO_FS_250
 * @see MPU6050_RA_GYRO_CONFIG
 * @see MPU6050_GCONFIG_FS_SEL_BIT
 * @see MPU6050_GCONFIG_FS_SEL_LENGTH
 */
void MPU6050_setFullScaleGyroRange(uint8_t range) {
    IICwriteBits(devAddr, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}

/************************** µœ÷∫Ø ˝********************************************
*∫Ø ˝‘≠–Õ:		void MPU6050_setFullScaleAccelRange(uint8_t range)
*π¶°°°°ƒ‹:	    …Ë÷√  MPU6050 º”ÀŸ∂»º∆µƒ◊Ó¥Û¡ø≥Ã
*******************************************************************************/
void MPU6050_setFullScaleAccelRange(uint8_t range) {
    IICwriteBits(devAddr, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}

/************************** µœ÷∫Ø ˝********************************************
*∫Ø ˝‘≠–Õ:		void MPU6050_setSleepEnabled(uint8_t enabled)
*π¶°°°°ƒ‹:	    …Ë÷√  MPU6050  «∑ÒΩ¯»ÎÀØ√ﬂƒ£ Ω
				enabled =1   ÀØæı
			    enabled =0   π§◊˜
*******************************************************************************/
void MPU6050_setSleepEnabled(uint8_t enabled) {
    IICwriteBit(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);
}

/************************** µœ÷∫Ø ˝********************************************
*∫Ø ˝‘≠–Õ:		uint8_t MPU6050_getDeviceID(void)
*π¶°°°°ƒ‹:	    ∂¡»°  MPU6050 WHO_AM_I ±Í ∂	 Ω´∑µªÿ 0x68
*******************************************************************************/
uint8_t MPU6050_getDeviceID(void) {

    IICreadBytes(devAddr, MPU6050_RA_WHO_AM_I, 1, buffer);
    return buffer[0];
}

/************************** µœ÷∫Ø ˝********************************************
*∫Ø ˝‘≠–Õ:		uint8_t MPU6050_testConnection(void)
*π¶°°°°ƒ‹:	    ºÏ≤‚MPU6050  «∑Ò“—æ≠¡¨Ω”
*******************************************************************************/
uint8_t MPU6050_testConnection(void) {
   if(MPU6050_getDeviceID() == 0x68)  //0b01101000;
   return 1;
   	else return 0;
}

/************************** µœ÷∫Ø ˝********************************************
*∫Ø ˝‘≠–Õ:		void MPU6050_setI2CMasterModeEnabled(uint8_t enabled)
*π¶°°°°ƒ‹:	    …Ë÷√ MPU6050  «∑ÒŒ™AUX I2Cœﬂµƒ÷˜ª˙
*******************************************************************************/
void MPU6050_setI2CMasterModeEnabled(uint8_t enabled) {
    IICwriteBit(devAddr, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_I2C_MST_EN_BIT, enabled);
}

/************************** µœ÷∫Ø ˝********************************************
*∫Ø ˝‘≠–Õ:		void MPU6050_setI2CBypassEnabled(uint8_t enabled)
*π¶°°°°ƒ‹:	    …Ë÷√ MPU6050  «∑ÒŒ™AUX I2Cœﬂµƒ÷˜ª˙
*******************************************************************************/
void MPU6050_setI2CBypassEnabled(uint8_t enabled) {
    IICwriteBit(devAddr, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_I2C_BYPASS_EN_BIT, enabled);
}

/************************** µœ÷∫Ø ˝********************************************
*∫Ø ˝‘≠–Õ:		void MPU6050_initialize(void)
*π¶°°°°ƒ‹:	    ≥ı ºªØ 	MPU6050 “‘Ω¯»Îø…”√◊¥Ã¨°£
*******************************************************************************/
void MPU6050_initialize(void) {
    MPU6050_setClockSource(MPU6050_CLOCK_PLL_YGYRO); //…Ë÷√ ±÷”
    MPU6050_setFullScaleGyroRange(MPU6050_GYRO_FS_2000);//Õ”¬›“«◊Ó¥Û¡ø≥Ã +-1000∂»√ø√Î
    MPU6050_setFullScaleAccelRange(MPU6050_ACCEL_FS_2);	//º”ÀŸ∂»∂»◊Ó¥Û¡ø≥Ã +-2G
    MPU6050_setSleepEnabled(0); //Ω¯»Îπ§◊˜◊¥Ã¨
	 MPU6050_setI2CMasterModeEnabled(0);	 //≤ª»√MPU6050 øÿ÷∆AUXI2C
	 MPU6050_setI2CBypassEnabled(0);	 //÷˜øÿ÷∆∆˜µƒI2C”Î	MPU6050µƒAUXI2C	÷±Õ®°£øÿ÷∆∆˜ø…“‘÷±Ω”∑√Œ HMC5883L
}




/**************************************************************************
∫Ø ˝π¶ƒ‹£∫MPU6050ƒ⁄÷√DMPµƒ≥ı ºªØ
»Îø⁄≤Œ ˝£∫Œﬁ
∑µªÿ  ÷µ£∫Œﬁ
◊˜    ’ﬂ£∫∆Ω∫‚–°≥µ÷Æº“
**************************************************************************/
void DMP_Init(void)
{ 
    u8 temp=0;

    i2cRead(0x68,0x75,1,&temp);
	uart0_send_string("IICËÆæÁΩÆÂÆåÊàê ......\r\n");//1
	if(temp!=0x68)NVIC_SystemReset();
   
	if(!mpu_init())
  {
	  if(!mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL))
	  	 uart0_send_string("ÊàêÂäüÂêØÁî®ÈôÄËû∫‰ª™XYZÂä†ÈÄüÂ∫¶ËÆ°XYZ ......\r\n");//2
	  if(!mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL))
	  	 uart0_send_string("ÈÖçÁΩÆFIFOÂÆåÊàê......\r\n");//3
	  if(!mpu_set_sample_rate(DEFAULT_MPU_HZ))
			uart0_send_string("ËÆæÁΩÆÈááÊ†∑Áéá:%d......\r\n");//4
	  if(!dmp_load_motion_driver_firmware())
	  if(!dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)))
	  	 uart0_send_string("ÊàêÂäüÂä†ËΩΩDMPÂõ∫‰ª∂......\r\n");//6
	  if(!dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
	        DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
	        DMP_FEATURE_GYRO_CAL))
	  	 uart0_send_string("ÊàêÂäüËÆæÁΩÆDMPÊñπÂêëÁü©Èòµ......\r\n");//7
	  if(!dmp_set_fifo_rate(DEFAULT_MPU_HZ))
			uart0_send_string("ËÆæÁΩÆDMPËæìÂá∫ÈÄüÁéá:%d......\r\n");//8
	  run_self_test();
	  if(!mpu_set_dmp_state(1))
	  	 uart0_send_string("ÊàêÂäüÂºÄÂêØDMPËΩ¨Êç¢......\r\n");//9 
  }
}
/**************************************************************************
∫Ø ˝π¶ƒ‹£∫∂¡»°MPU6050ƒ⁄÷√DMPµƒ◊ÀÃ¨–≈œ¢
»Îø⁄≤Œ ˝£∫Œﬁ
∑µªÿ  ÷µ£∫Œﬁ
◊˜    ’ﬂ£∫∆Ω∫‚–°≥µ÷Æº“
**************************************************************************/
u8 Read_DMP(float *Pitch,float *Roll,float *Yaw,u8 * more)
{	
	float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;
	unsigned long sensor_timestamp;
	long quat[4];

	if(dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors, more))
	{
		return 1;
	}
	
	if (sensors)//& INV_WXYZ_QUAT
	{    
		 q0=quat[0] / q30;
		 q1=quat[1] / q30;
		 q2=quat[2] / q30;
		 q3=quat[3] / q30;
		 *Pitch = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3; 	
		 *Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
	     *Yaw   = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;	//yaw

	}
	return 0;

}

/**************************************************************************
∫Ø ˝π¶ƒ‹£∫∂¡»°MPU6050ƒ⁄÷√Œ¬∂»¥´∏–∆˜ ˝æ›
»Îø⁄≤Œ ˝£∫Œﬁ
∑µªÿ  ÷µ£∫…„ œŒ¬∂»
**************************************************************************/
int Read_Temperature(void)
{	   
	  float Temp;
	  Temp=(I2C_ReadOneByte(devAddr,MPU6050_RA_TEMP_OUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_TEMP_OUT_L);
		if(Temp>32768) Temp-=65536;
		Temp=(36.53+Temp/340)*10;
	  return (int)Temp;
}

/***********************************************
π¶ƒ‹£∫∂¡»°æ¿’˝ŒÛ≤Ó∫Ûµƒ◊ÀÃ¨


***********************************************/
unsigned char more;
#define jiusu_max 6001
#define jiusu_star 5001
#define DIV jiusu_max-jiusu_star

//#include <ti/iqmath/include/IQmathLib.h>
//u8 Read_DMP(float *Pitch, float *Roll, float *Yaw, u8 *more)
//{
//    // 1. ∂®“ÂQ30∏Ò Ω¥Ê¥¢‘≠ º ˝æ›£¨Q29∏Ò Ω”√”⁄»˝Ω«∫Ø ˝‘ÀÀ„
//    _iq30 q0_q30 = _IQ30(1.0f), q1_q30 = _IQ30(0.0f), q2_q30 = _IQ30(0.0f), q3_q30 = _IQ30(0.0f);
//    _iq29 q0, q1, q2, q3;  // Q29∏Ò Ω”√”⁄»˝Ω«∫Ø ˝
//    unsigned long sensor_timestamp;
//    long quat[4];

//    if (dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors, more))
//    {
//        return 1;
//    }
//    
//    if (sensors) 
//    {    
//        // 2. ∂¡»°Q30∏Ò Ω‘≠ º ˝æ›
//        q0_q30 = ( _iq30 )quat[0];
//        q1_q30 = ( _iq30 )quat[1];
//        q2_q30 = ( _iq30 )quat[2];
//        q3_q30 = ( _iq30 )quat[3];
//        
//        // 3. Q30◊™Q29£®”““∆1Œª£©
//        q0 = q0_q30 >> 1;
//        q1 = q1_q30 >> 1;
//        q2 = q2_q30 >> 1;
//        q3 = q3_q30 >> 1;
//        
//        // --------------------- ◊ÀÃ¨Ω‚À„£®Q29∂®µ„ ˝‘ÀÀ„£© ---------------------
//        // º∆À„Pitch£∫asin(-2*q1*q3 + 2*q0*q2)
//        _iq29 pitch_term = _IQ29rsmpy(_IQ29rsmpy(_IQ29(-2.0f), q1), q3) + _IQ29rsmpy(_IQ29rsmpy(_IQ29(2.0f), q0), q2);
//        _iq29 pitch_rad = _IQ29asin(pitch_term);  // Q29∏Ò Ωª°∂»÷µ
//        
//        // º∆À„Roll£∫atan2(2*q2*q3 + 2*q0*q1, -2*q1*q1 - 2*q2*q2 + 1)
//        _iq29 roll_num = _IQ29rsmpy(_IQ29rsmpy(_IQ29(2.0f), q2), q3) + _IQ29rsmpy(_IQ29rsmpy(_IQ29(2.0f), q0), q1);
//        _iq29 roll_den = _IQ29(1.0f) - _IQ29rsmpy(_IQ29rsmpy(_IQ29(2.0f), q1), q1) - _IQ29rsmpy(_IQ29rsmpy(_IQ29(2.0f), q2), q2);
//        _iq29 roll_rad = _IQ29atan2(roll_num, roll_den);
//        
//        // º∆À„Yaw£∫atan2(2*(q1*q2 + q0*q3), q0*q0+q1*q1-q2*q2-q3*q3)
//        _iq29 yaw_num = _IQ29rsmpy(_IQ29(2.0f), _IQ29rsmpy(q1, q2)+ _IQ29rsmpy(q0, q3));
//        _iq29 yaw_den = (_IQ29rsmpy(q0, q0)+ _IQ29rsmpy(q1, q1))-(_IQ29rsmpy(q2, q2)+ _IQ29rsmpy(q3, q3));
//        _iq29 yaw_rad = _IQ29atan2(yaw_num, yaw_den);
// //					 *Pitch = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3; 	
////					 *Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
////				   *Yaw   = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;	//yaw       
//        // --------------------- Q29◊™Q30£®◊Û“∆1Œª£© ---------------------
////        _iq30 pitch_rad_q30 = pitch_rad << 1;
////        _iq30 roll_rad_q30 = roll_rad << 1;
////        _iq30 yaw_rad_q30 = yaw_rad << 1;
//        // --------------------- ∂®µ„ ˝◊™∏°µ„ ˝£®Ω«∂»◊™ªª£© ---------------------
//        *Pitch = _IQ29toF(pitch_rad) * 57.3f;
//        *Roll = _IQ29toF(roll_rad) * 57.3f;
//        *Yaw = _IQ29toF(yaw_rad) * 57.3f;
//    }
//    
//    return 0;
//}
void Read_DMP_Correct_error_data(float *Pitch,float*Roll,float*Yaw,unsigned char* flag,unsigned short *MPU_ZhunBei_jisu)
{
	
	static float Fir_Yaw=0,Average_Error=0,jisuan_error=0;
	
//	  printf("%f\n",*Yaw);
		Read_DMP(Pitch,Roll,Yaw,&more);
		
		if(*MPU_ZhunBei_jisu<jiusu_max)
		{
			(*MPU_ZhunBei_jisu)++;
		}
		if((*MPU_ZhunBei_jisu)>=(jiusu_star-1)&(*MPU_ZhunBei_jisu)<jiusu_max)
		{
			if((*MPU_ZhunBei_jisu)==jiusu_star-1)
			{
				printf("kaishi\n");
				Fir_Yaw=*Yaw;
			}
			
			
			Average_Error+=((*Yaw)-Fir_Yaw);
			Fir_Yaw=*Yaw;
			if ((*MPU_ZhunBei_jisu)==jiusu_max-1)
			{
				*flag=1;
				start_Yaw=*Yaw;
				Average_Error/=DIV;
				mpu_set_sample_rate(20);
				dmp_set_fifo_rate(20);
			}
		}
		else if((*MPU_ZhunBei_jisu)>=jiusu_max)
		{
			jisuan_error+=Average_Error;
			(*Yaw)-=jisuan_error;
			if(jisuan_error>360)
			{
				jisuan_error-=360;
			}
			else if(jisuan_error<-360)
			{
				jisuan_error+=360;
			}
			if (*Yaw < -180) 
			{
				(*Yaw) += 360;
			} 
			else if (*Yaw > 180) 
			{ 
					(*Yaw) -= 360;
			}
		}
}


/**************************************************************************
∫Ø ˝π¶ƒ‹£∫Õ‚≤ø÷–∂œ≥ı ºªØ
»Îø⁄≤Œ ˝£∫Œﬁ
∑µªÿ  ÷µ£∫Œﬁ 
**************************************************************************/
void MPU6050_INT_Ini(void)
{  
	
	
	
	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	EXTI_InitTypeDef EXTI_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//Õ‚≤ø÷–∂œ£¨–Ë“™ πƒ‹AFIO ±÷”
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // πƒ‹PB∂Àø⁄ ±÷”
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	            //∂Àø⁄≈‰÷√
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //…œ¿≠ ‰»Î
//	GPIO_Init(GPIOB, &GPIO_InitStructure);					      //∏˘æ›…Ë∂®≤Œ ˝≥ı ºªØGPIOB 
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//œ¬Ωµ—ÿ¥•∑¢
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//∏˘æ›EXTI_InitStruct÷–÷∏∂®µƒ≤Œ ˝≥ı ºªØÕ‚…ËEXTIºƒ¥Ê∆˜
//		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			// πƒ‹∞¥º¸À˘‘⁄µƒÕ‚≤ø÷–∂œÕ®µ¿
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//«¿’º”≈œ»º∂2£¨ 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//◊””≈œ»º∂1
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								// πƒ‹Õ‚≤ø÷–∂œÕ®µ¿
//  	NVIC_Init(&NVIC_InitStructure); 

}
//------------------End of File----------------------------
