#include "PID.h"
#include "ti_msp_dl_config.h"
#include "usart.h"
#include "xunji.h"
#include "main.h"
float P_out=0,I_out=0,D_out=0,erro=0;
/***********************************************************************************

 功能：pid结构体赋值

 参数：out_min最小值，out_max最大值

***********************************************************************************/
void PID_Init(PID *pid, float Kp, float Ki, float Kd )
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->error_j = 0;//误差累加
		pid->error_last=0;//上次误差
		pid->error=0;//误差
		pid->error_Last_Last=0;//上上次误差
		pid->Out_Pu=0;//输出
		pid->OUT_j=0;
}
/***********************************************************************************

 功能：输出限幅

 参数：value需要限幅的值，max限幅

 返回：限幅后的值

更改人：吴贵麒

建议：删了

***********************************************************************************/
short Limit_Output(short value,  short max)
{
    if(value > max)
        return max;
    else if(value < (-1)*max)
        return (-1)*max;
    else
        return value;
}
/***********************************************************************************

 功能：pid计算,增量式pid_out+=Kp*(error-Last_error)+Ki*error+Kd(error-2Last_error+Last_Last_error)

 参数：PID *pid参数，setpoint设定的值，newpoint传过来的值

 返回：Out_Put输出


更改人：吴贵麒
为PID的平滑增加了一些限幅如下：
newpoint：防止错误数据
pid->error：减少+到-的抖动
temp：正时，数字越小加速越慢，负数，过大会出现减速停转
pid->Out_Pu：系统控制用=周期-1(最大一定要减一，PWM模式要求的)
***********************************************************************************/
float tem1=0,out2=0;
short PID_Increment(PID *pid, short setpoint,short newpoint)
{
	float temp=0;
	if(newpoint>800)
	{
		return pid->Out_Pu;
	}
	else if(newpoint<-800)
	{
		return pid->Out_Pu;
	}
	pid->error=setpoint-newpoint;
	if(pid->error>1200)
	{
		pid->error=1200;
	}
	else if(pid->error<-1200)
	{
		pid->error=-1200;
	}
	I_out=(pid->Ki*pid->error);//积分项
	P_out=(pid->Kp*(pid->error-pid->error_last));//比例项
	
	D_out=(pid->Kd*(pid->error-2*pid->error_last+pid->error_Last_Last));//微分项

	pid->error_Last_Last=pid->error_last;
	pid->error_last=pid->error;
	temp=P_out+I_out+D_out;
	if (temp>3000)
	{
		temp=3000;
	}	
	
	if (temp<-2400)
	{
		temp=-2400;
	}
	pid->OUT_j=(pid->OUT_j+temp)*0.3+pid->OUT_j	*0.7;
	pid->Out_Pu=(short)(pid->OUT_j);
	//tem1=temp;
		if(pid->Out_Pu>50)
	{
		pid->Out_Pu+=200;
	}
	else if(pid->Out_Pu<-50)
	{
		pid->Out_Pu-=200;
	}
	if(pid->OUT_j>5000)
	{
		pid->OUT_j=5000;
	}
	else if(pid->OUT_j<-4000)
	{
		pid->OUT_j=-4000;
	}
	if (pid->Out_Pu>999)
		pid->Out_Pu=999;
	if (pid->Out_Pu<-999)
	{
		pid->Out_Pu=-999;
	}
	return pid->Out_Pu;
}



short PID_Zhixian(PID *pid, float temp_YAW)
{
	float K_P=0,K_D=0;
	
	pid->error=temp_YAW*5;
	
	K_P=pid->Kp*pid->error;
	K_D=pid->Kd*(pid->error-pid->error_last);
	
	pid->error_last=pid->error;
	
	pid->Out_Pu=(short)K_P+(short)K_D;
//	pid->Out_Pu=last_out*0.8+pid->Out_Pu*0.2;
	if(pid->Out_Pu>400)
	{
		pid->Out_Pu=400;
	}
	if(pid->Out_Pu<-400)
	{
		pid->Out_Pu=-400;
	}
//	last_out=pid->Out_Pu;
	return pid->Out_Pu;
}
short PID_XunJi(PID *pid,unsigned char BaiZheng)
{
	
	float KP_a=0,KD_a=0;
	WuCha_Munber=0;
	unsigned char LED_Shuliang=0;
	for(int i=0;i<16;i++)
	{
		if(temp_left_w&0x01<<i)
		{
			if(i<2)
			{
				WuCha_Munber+=5;
			}
			else if(i>=2&&i<5)
			{
				WuCha_Munber+=8;
			}
			else if(i>=5&&i<11)
			{
				WuCha_Munber+=18;
			}
			else 
			{
				WuCha_Munber+=30;
			}
		}
		if(temp_right_w&0x01<<i)
		{
			if(i<2)
			{
				WuCha_Munber-=5;
			}
			else if(i>=2&&i<5)
			{
				WuCha_Munber-=8;
			}
			else if(i>=5&&i<11)
			{
				WuCha_Munber-=18;
			}
			else 
			{
				WuCha_Munber-=30;
			}			
		}
	}
	WuCha_Munber/=LED_Num;
	pid->error=WuCha_Munber;
	
	KP_a=pid->Kp*pid->error;
	
	KD_a=pid->Kd*(pid->error-pid->error_last);
	
	pid->Out_Pu=(short)KP_a+(short)KD_a;
	
	pid->error_last=pid->error;
	
	if(pid->Out_Pu>65)
	{
		pid->Out_Pu=65;
	}
	if(pid->Out_Pu<-65)
	{
		pid->Out_Pu=-65;
	}
	if(BaiZheng==1)
	{
		if(pid->Out_Pu<0)
		{
			pid->Out_Pu=-pid->Out_Pu;
		}	
	}
	else if(BaiZheng==2)
	{
		if(pid->Out_Pu>0)
		{
			pid->Out_Pu=-pid->Out_Pu;
		}	
	}
	
	return pid->Out_Pu;
}

/***********************************************************************************

 功能：pid计算,位置式pid_out=Kp*error+Ki*(eror+=error)+Kd*(error-error_Last)

 参数：PID *pid参数，setpoint设定的值，newpoint传过来的值

 返回：output输出

***********************************************************************************/
short PID_JiSuan(PID *pid, short setpoint,short newpoint) 
{
	short  error=(setpoint-newpoint);// 计算误差
	erro=(short)error;
	pid->error_j+=error;// 积分累加
	//积分限幅
	if(pid->error_j>50)
			pid->error_j=50;
	if(pid->error_j<-50)
		pid->error_j=-50;
	
	P_out=(short)(pid->Kp * error);		
		
	I_out=(short)(pid->Ki*pid->error_j);	
		
	D_out=(short)(pid->Kd*(pid->error_last-error));
	
	pid->Out_Pu =(short)(P_out+I_out+D_out );
	
	pid->error_last=error;
	if (pid->Out_Pu>20)
		pid->Out_Pu=20;
	else if(pid->Out_Pu<-20)
		pid->Out_Pu=20;
	return pid->Out_Pu;
}
/***********************************************************************************

 功能：指数运算函数

 参数：Cu要立方的数，Be多少立方

 返回：Cu的指数

***********************************************************************************/
unsigned int Cube(unsigned int Cu,unsigned int Be)
{
	unsigned int Ten=1;
	unsigned int Above=Be;
	if(Above==0)
		return 1;
	while(Above)
	{
		Ten*=Cu;
		Above--;
	}
	return Ten;
}
/***********************************************************************************

功能：int类型数字转字符串发送

参数：number传入的数字，buffer[40]存储数组，拆分传入的number，然后分开传入buffer[40]

返回：number的长度

***********************************************************************************/
unsigned char write_cann(int number,unsigned char  buffer[40])
{
	int DigitCount=0;
	unsigned char test2;
	int teap=number;
	unsigned char Length=0;
	//判断是否为负数
	if(teap<0)
	{
		buffer[Length++]='-';
		teap=-teap;
		number=-number;
	}
	//计数
	while(teap)
	{
		teap/=10;
		DigitCount++;
	}
	//如果接收到0
	if (number==0)
	{
		buffer[Length++]=0+'0';
		return Length;
	}
	if(number>0)
	{
		while(DigitCount)
		{
			DigitCount--;
			buffer[Length++]='0'+number/Cube(10,DigitCount)%10;
		}
	
	}
	return Length;
}

/***********************************************************************************

功能：数字转字符串（支持 int 和 float）

参数：number 传入的数字转成字符串，分别存储在buffe,默认保留2的小数位数6 *10.4%10

返回：number的长度
      
***********************************************************************************/
unsigned char write_String(float number, unsigned char buffer[40]) 
{

    unsigned char len = 0;
	int DigitCount = 0;//整数长度
    int int_part = (int)number;//整数部分
    float decimal_part = number - int_part; // 小数部分 
    unsigned char decimal_places = 6;  // 最多检查6位小数
    unsigned char actual_decimal_places = 0;//实际最后0的位置
    unsigned char decimal_digits[6] = {0};//存放后六位的点

    // 处理负数
    if (number < 0)
	{
        buffer[len++] = '-';
        int_part = -int_part;
		decimal_part=-decimal_part;
    }

    // 处理整数部分，
    if (int_part == 0) 
	{
        buffer[len++] = '0';//传空
    } 
	else 
	{
        int temp = int_part;
        
        
        // 计算整数位数长度
        while (temp > 0) 
		{
            temp /= 10;
            DigitCount++;
        }
		while(DigitCount)
		{
			DigitCount--;
		    buffer[len++] = '0' + (int_part / Cube(10,DigitCount ) % 10);
		}

    }



    for (int i = 0; i < decimal_places; i++) //循例6次，检查是否有0
	{
        decimal_part *= 10;
        decimal_digits[i] = (int)decimal_part % 10;//临时把后面六位小数存在里面
        if (decimal_digits[i] != 0) //判断是否为0
		{
            actual_decimal_places = i + 1;  // 记录最后非零位的位置
        }
    }

    // 如果有有效小数位，写入小数点和小数部分
    if (actual_decimal_places > 0) 
	{
        buffer[len++] = '.';
        for (int i = 0; i < actual_decimal_places; i++) 
		{
            buffer[len++] = '0' + decimal_digits[i];
        }
    }

    return len;
}

/***********************************************************************************

功能：接收串口的数据ASCLL值，调整pid的值

参数：pid定义的结构体，unsigned char arr[40]接收的数组

***********************************************************************************/
void Munber_Count(PID *pid,unsigned char * arr)
{
	float kp=0,ki=0,kd=0;//结构体定义的值
	unsigned char Decimal;//小数标志位
	unsigned char Comma=0;//逗号标志位
	unsigned char Count=0;//计数，记录数组运行位置
	float New_Mun=0.0;//要赋给的值
	float Divisor=1.0;//小数的被除数
	unsigned char AShift=0;//单个数组接收的数
	int Plus_flag=1;//正负标志位
	while(Count < 40 && arr[Count]!='\n')
	{
		if(arr[Count] == '-')
		{
			Plus_flag=-1;
		}
		else if(arr[Count] == ',')
		{
			Comma++;
			if(Comma == 1)
				kp=New_Mun*Plus_flag;
			if(Comma == 2)
				ki=New_Mun*Plus_flag;
			if(Comma > 0 && Comma < 3)
			{
				Decimal=0;
				New_Mun=0;
				Divisor=1.0;
				Plus_flag=1;
			}
		}
		else if(arr[Count]== '.')
		{
			Decimal=1;
		}
		else if(arr[Count] >= '0' && arr[Count] <= '9')
		{
			AShift=arr[Count]-'0';
			if(Decimal!=1)
			{
				New_Mun=New_Mun*10+AShift;
			}
			else
			{
				Divisor/=10;
				New_Mun+=AShift*Divisor;
			}
		}
		else
		{
			return;
		}
		Count++;
	}
	if(Comma==2&&arr[Count]<40)
	{
		kd=New_Mun*Plus_flag;
	}
	pid->Kp=kp;
	pid->Ki=ki;
	pid->Kd=kd;
	
}





////typedef unsigned short uint16_t;
////typedef unsigned char 	uint8_t;
//// 指数运算函数，处理溢出和无符号数递减问题
//uint16_t sqrt1(uint8_t base, uint8_t exponent) {
//    uint16_t result = 1;
//    // 处理指数为0的情况
//    if (exponent == 0) return 1;
//    // 使用无符号数循环时避免负数，改为从exponent递减到1
//    for (uint8_t i = 1; i <= exponent; i++) {
//        result *= base;
//    }
//    return result;
//}











