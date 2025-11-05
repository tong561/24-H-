#include "IIC.h"
#include "ti_msp_dl_config.h"
//#include "delay.h"

void IIC_Delay(void)
{
	my_delay_us(1);
}
//设置SDA输出模式


//初始化IIC
void IIC_Init(void)
{				
//	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	//使能GPIOB时钟
//	   
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD ;   //推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOA,GPIO_Pin_10|GPIO_Pin_11); 	//PB6,PB7 输出高
}


/******************************************************************
 * 函 数 名 称：IIC_Start
 * 函 数 说 明：IIC起始时序
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void IIC_Start(void)//dui
{
	SDA_OUT();
	SCL_SET;
	SDA_RESET;
	SDA_SET;
	//my_delay_us(1);
	SDA_RESET;
	SCL_RESET;
}
/******************************************************************
 * 函 数 名 称：IIC_Stop
 * 函 数 说 明：IIC停止信号
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void IIC_Stop(void)//对
{
	SDA_OUT();
	SDA_RESET;
	
	SCL_SET;
	//my_delay_us(1);
	SDA_SET;
}
/******************************************************************
 * 函 数 名 称：IIC_Sand_ASK
 * 函 数 说 明：主机发送应答或者非应答信号
 * 函 数 形 参：0发送应答  1发送非应答
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void IIC_Sand_ASK(unsigned char ASK)//0应答//dui
{
	SDA_OUT();
	SCL_RESET;
	if(ASK){
		SDA_SET;}
	else {
		SDA_RESET;}
	__NOP();
	//delay_us(1);
	SCL_SET;
	__NOP();
	//delay_us(1);
	SCL_RESET;
	SDA_SET;
}
/******************************************************************
 * 函 数 名 称：IIC_Read_ASK
 * 函 数 说 明：等待从机应答
 * 函 数 形 参：无
 * 函 数 返 回：0有应答  1超时无应答
 * 作       者：LC
 * 备       注：无
******************************************************************/
unsigned char IIC_Read_ASK(void)//0应答读//对
{
	SCL_SET;
	SDA_IN();
	//delay_us(1);
	if(SDA_GET())
	{
		SCL_RESET;
		return  1;
	}
	else 
	{
		SCL_RESET;
		return 0;
	}
}
/******************************************************************
 * 函 数 名 称：IIC_Sand
 * 函 数 说 明：写入一个字节
 * 函 数 形 参：dat要写人的数据
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void IIC_Sand(unsigned char data)//对
{
	SDA_OUT();
	for(unsigned char i=0;i<8;i++)
	{
		if(data & (0x80 >> i))
		{SDA_SET;}
		else
		{SDA_RESET;}
		//delay_us(1);
		SCL_SET;
		//delay_us(1);
		SCL_RESET;
	}
	SDA_SET;
}
/******************************************************************
 * 函 数 名 称：IIC_Read8
 * 函 数 说 明：IIC读时序
 * 函 数 形 参：无
 * 函 数 返 回：读到的数据
 * 作       者：LC
 * 备       注：无
******************************************************************/
unsigned char IIC_Read8(void)//对
{
	SDA_IN();
	unsigned char i,data=0;
	for(i=0;i<8;i++)
	{
		SCL_SET;
		data<<=1;
		if (SDA_GET())
			data|=0x01;
		SCL_RESET;
	}
	
	return data;
}

//u8 IIC_Wait_Ack(void)
//{
//	u8 ucErrTime=0;
//	SDA_SET;IIC_Delay();	   
//	SCL_SET;IIC_Delay();	 
//	while(READ_SDA)
//	{
//		ucErrTime++;
//		if(ucErrTime>100)
//		{
//			IIC_Stop();   //
//			return 0;
//		}
//		IIC_Delay();
//	}
//	SCL_RESET;//时钟输出0 	   
//	return 1;  
//} 

//****************************
//
//********添加代码************
//
/**************************实现函数********************************************
*函数原型:		bool i2cWrite(uint8_t addr, uint8_t reg, uint8_t data)
*功　　能:		
*******************************************************************************/
int i2cWrite(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data)
{
		int i;
		IIC_Start();
    IIC_Sand(addr << 1 );
    if (IIC_Read_ASK()) {
        IIC_Stop();
        return 1;
    }
    IIC_Sand(reg);
    IIC_Read_ASK();
		for (i = 0; i < len; i++) {
        IIC_Sand(data[i]);
        if (IIC_Read_ASK()) {
            IIC_Stop();
            return 0;
        }
    }
    IIC_Stop();
    return 0;
}
/**************************实现函数********************************************
*函数原型:		bool i2cWrite(uint8_t addr, uint8_t reg, uint8_t data)
*功　　能:		
*******************************************************************************/
int i2cRead(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
	IIC_Start();
    IIC_Sand(addr << 1);
    if(IIC_Read_ASK()) {
        IIC_Stop();
        return 1;
    }
    IIC_Sand(reg);
    IIC_Read_ASK();
    IIC_Start();
    IIC_Sand((addr << 1)+1);
    IIC_Read_ASK();
    while (len) {
        if (len == 1)
				{
            *buf = IIC_Read8();
						IIC_Sand_ASK(1);
				}
        else
				{
          *buf = IIC_Read8();
					IIC_Sand_ASK(0);
				}
        buf++;
        len--;
    }
    IIC_Stop();
    return 0;
}
/**************************实现函数********************************************
*函数原型:		unsigned char I2C_ReadOneByte(unsigned char I2C_Addr,unsigned char addr)
*功　　能:	    读取指定设备 指定寄存器的一个值
输入	I2C_Addr  目标设备地址
		addr	   寄存器地址
返回   读出来的值
*******************************************************************************/ 
unsigned char I2C_ReadOneByte(unsigned char I2C_Addr,unsigned char addr)
{
	unsigned char res=0;
	
	IIC_Start();	
	IIC_Sand(I2C_Addr);	   //发送写命令
	res++;
	IIC_Read_ASK();
	IIC_Sand(addr); res++;  //发送地址
	IIC_Read_ASK();	  
	//IIC_Stop();//产生一个停止条件	
	IIC_Start();
	IIC_Sand(I2C_Addr+1); res++;          //进入接收模式			   
	IIC_Read_ASK();
	res=IIC_Read8();
	IIC_Sand_ASK(1);	   
    IIC_Stop();//产生一个停止条件

	return res;
}


/**************************实现函数********************************************
*函数原型:		u8 IICreadBytes(u8 dev, u8 reg, u8 length, u8 *data)
*功　　能:	    读取指定设备 指定寄存器的 length个值
输入	dev  目标设备地址
		reg	  寄存器地址
		length 要读的字节数
		*data  读出的数据将要存放的指针
返回   读出来的字节数量
*******************************************************************************/ 
u8 IICreadBytes(u8 dev, u8 reg, u8 length, u8 *data){
    u8 count = 0;
	
	IIC_Start();
	IIC_Sand(dev);	   //发送写命令
	IIC_Read_ASK();
	IIC_Sand(reg);   //发送地址
    IIC_Read_ASK();	  
	IIC_Start();
	IIC_Sand(dev+1);  //进入接收模式	
	IIC_Read_ASK();
	
    for(count=0;count<length;count++){
		 
		 if(count!=length-1)
		 {
			 data[count]=IIC_Read8();
			IIC_Sand_ASK(0);  //带ACK的读数据
		 }
		 	else  
			{
				data[count]=IIC_Read8();
				IIC_Sand_ASK(1);	 //最后一个字节NACK
			}
	}
    IIC_Stop();//产生一个停止条件
    return count;
}

/**************************实现函数********************************************
*函数原型:		u8 IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data)
*功　　能:	    将多个字节写入指定设备 指定寄存器
输入	dev  目标设备地址
		reg	  寄存器地址
		length 要写的字节数
		*data  将要写的数据的首地址
返回   返回是否成功
*******************************************************************************/ 
u8 IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data){
  
 	u8 count = 0;
	IIC_Start();
	IIC_Sand(dev);	   //发送写命令
	IIC_Read_ASK();
	IIC_Sand(reg);   //发送地址
    IIC_Read_ASK();	  
	for(count=0;count<length;count++){
		IIC_Sand(data[count]); 
		IIC_Read_ASK(); 
	 }
	IIC_Stop();//产生一个停止条件

    return 1; //status == 0;
}

/**************************实现函数********************************************
*函数原型:		u8 IICreadByte(u8 dev, u8 reg, u8 *data)
*功　　能:	    读取指定设备 指定寄存器的一个值
输入	dev  目标设备地址
		reg	   寄存器地址
		*data  读出的数据将要存放的地址
返回   1
*******************************************************************************/ 
u8 IICreadByte(u8 dev, u8 reg, u8 *data){
	*data=I2C_ReadOneByte(dev, reg);
    return 1;
}

/**************************实现函数********************************************
*函数原型:		unsigned char IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data)
*功　　能:	    写入指定设备 指定寄存器一个字节
输入	dev  目标设备地址
		reg	   寄存器地址
		data  将要写入的字节
返回   1
*******************************************************************************/ 
unsigned char IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data){
    return IICwriteBytes(dev, reg, 1, &data);
}

/**************************实现函数********************************************
*函数原型:		u8 IICwriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data)
*功　　能:	    读 修改 写 指定设备 指定寄存器一个字节 中的多个位
输入	dev  目标设备地址
		reg	   寄存器地址
		bitStart  目标字节的起始位
		length   位长度
		data    存放改变目标字节位的值
返回   成功 为1 
 		失败为0
*******************************************************************************/ 

u8 IICwriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data)
{

    u8 b;
    if (IICreadByte(dev, reg, &b) != 0) {
        u8 mask = (0xFF << (bitStart + 1)) | 0xFF >> ((8 - bitStart) + length - 1);
        data <<= (8 - length);
        data >>= (7 - bitStart);
        b &= mask;
        b |= data;
        return IICwriteByte(dev, reg, b);
    } else {
        return 0;
    }
}

/**************************实现函数********************************************
*函数原型:		u8 IICwriteBit(u8 dev, u8 reg, u8 bitNum, u8 data)
*功　　能:	    读 修改 写 指定设备 指定寄存器一个字节 中的1个位
输入	dev  目标设备地址
		reg	   寄存器地址
		bitNum  要修改目标字节的bitNum位
		data  为0 时，目标位将被清0 否则将被置位
返回   成功 为1 
 		失败为0
*******************************************************************************/ 
u8 IICwriteBit(u8 dev, u8 reg, u8 bitNum, u8 data){
    u8 b;
    IICreadByte(dev, reg, &b);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    return IICwriteByte(dev, reg, b);
}

//------------------End of File----------------------------



























