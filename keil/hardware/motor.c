#include "motor.h"
short test_left=0,test_right=0;
PID XunJi_error;
PID Zhixian;
PID pid_left;
PID pid_right;
signed short left_ZhuanSu=0,right_ZhuanSu=0;//左右计算转速
unsigned char Direction_left_flag=1,Direction_right_flag=1;
float start_Yaw=0;

//float app=0;
/***********************************************
电机控制：
PWM：控制速度0-> +-999(符号控制正反转)
**********************************************/

/*************************************************
功能：左轮pwm
**************************************************/
void motor_Left( short PWM)
{
		if(PWM>=0)
		{
			Direction_left_flag=1;
			DL_TimerG_setCaptureCompareValue(MOTOR_PWM_INST,PWM,MOTOR_LEFT_IDX);
			DL_GPIO_clearPins(motor_PORT,motor_left_2_PIN);//行驶方向
			DL_GPIO_setPins  (motor_PORT,motor_left_1_PIN);

		}
		else 
		{
			Direction_left_flag=0;
			DL_TimerG_setCaptureCompareValue(MOTOR_PWM_INST,-PWM,MOTOR_LEFT_IDX);
			DL_GPIO_clearPins(motor_PORT,motor_left_1_PIN);//行驶方向
			DL_GPIO_setPins  (motor_PORT,motor_left_2_PIN);
		}
	
}


/*************************************************
功能：右轮pwm
**************************************************/
void motor_Right( short PWM)
{
	if(PWM>=0)
	{
		Direction_right_flag=1;
		DL_TimerG_setCaptureCompareValue(MOTOR_PWM_INST,PWM,MOTOR_RIGHT_IDX);	
		DL_GPIO_clearPins(motor_PORT,motor_right_1_PIN);
		DL_GPIO_setPins  (motor_PORT,motor_right_2_PIN);
	}
	else 
	{
		
		Direction_right_flag=0;
		DL_TimerG_setCaptureCompareValue(MOTOR_PWM_INST,-PWM,MOTOR_RIGHT_IDX);	
		DL_GPIO_clearPins(motor_PORT,motor_right_2_PIN);
		DL_GPIO_setPins  (motor_PORT,motor_right_1_PIN);
		
	}
}
/*************************************************
功能：控制轮胎停止急刹车
**************************************************/
unsigned char motor_stop(void)
{
	static unsigned char motor_stop_flag=0;
	motor_stop_flag++;
	if(motor_stop_flag<20)
	{
		left_ZhuanSu=-2000;
		right_ZhuanSu=-2000;
		
		DL_TimerG_setCaptureCompareValue(MOTOR_PWM_INST,750,MOTOR_LEFT_IDX);//left
		DL_TimerG_setCaptureCompareValue(MOTOR_PWM_INST,750,MOTOR_RIGHT_IDX);//right	
		DL_GPIO_clearPins(motor_PORT,motor_left_1_PIN);//行驶方向反转
		DL_GPIO_setPins  (motor_PORT,motor_left_2_PIN);		
		DL_GPIO_clearPins(motor_PORT,motor_right_2_PIN);
		DL_GPIO_setPins  (motor_PORT,motor_right_1_PIN);
	}
	else
	{
		
		PID_Init(&pid_left,6.0,0.015,2.0);//5.0,0.06,2.0
		PID_Init(&pid_right,6.0,0.015,2.0);//5.0,0.06,2.0
		DL_TimerG_setCaptureCompareValue(MOTOR_PWM_INST,0,MOTOR_LEFT_IDX);//left
		DL_TimerG_setCaptureCompareValue(MOTOR_PWM_INST,0,MOTOR_RIGHT_IDX);//right	
		DL_GPIO_clearPins(motor_PORT,motor_left_2_PIN);//行驶方向正传
		DL_GPIO_setPins  (motor_PORT,motor_left_1_PIN);		
		DL_GPIO_clearPins(motor_PORT,motor_right_1_PIN);
		DL_GPIO_setPins  (motor_PORT,motor_right_2_PIN);
		motor_stop_flag=0;
		return 1;
	}
	return 0;
}
/*************************************************
功能：直线
**************************************************/
void motor_run_line(float qidai_Yaw,unsigned short V)
{	
	short  error=0;
	short temp_jian=0,temp_jia=0;
	float temp_YAW=0;
	temp_YAW=qidai_Yaw-Yaw;
	if(temp_YAW>180)
		temp_YAW-=360;
	else if(temp_YAW<-180)
		temp_YAW+=360;
//	app=temp_YAW;//测试
	error=PID_Zhixian(&Zhixian,temp_YAW);
//	error=(short)(temp_YAW*6);
	temp_jian=V-error;
	temp_jia=V+error;
	left_ZhuanSu=temp_jian;
	right_ZhuanSu=temp_jia;
//	motor_Left(PID_Increment(&pid_left,left_ZhuanSu,left_cap));//600
//	motor_Right(PID_Increment(&pid_right,right_ZhuanSu,right_cap));
}
/*************************************************
功能：黑线
**************************************************/
//void motor_run_xunji(unsigned short V,unsigned char BaiZheng)
//{
//	short temp_left=0,temp_right=0,pid_out=0;
//	pid_out=PID_XunJi(&XunJi_error, BaiZheng);
//	
//	temp_left=V-(signed short)pid_out;
//	temp_right=V+(signed short)pid_out;
//	
//	left_ZhuanSu=temp_left;
//	right_ZhuanSu=temp_right;
//	//左右速差最多1.3倍速
//	if(left_ZhuanSu>V+30)
//	{
//		left_ZhuanSu=V+30;
//	}
//	if(right_ZhuanSu>V+30)
//	{
//		right_ZhuanSu=V+30;
//	}	
//	if(temp_left<0)
//		left_ZhuanSu=0;
//	else if(temp_right<0)
//		right_ZhuanSu=0;
//}
/*************************************************
功能：限幅
**************************************************/
//void  XianSu_Judge(short * shiji_left_V,short * shiji_right_V )
//{
//		if(left_ZhuanSu-(*shiji_left_V)>xiansu)
//			 (*shiji_left_V)+=xiansu;
//		 else if(left_ZhuanSu-(*shiji_left_V)<-xiansu)
//			 (*shiji_left_V)-=xiansu;
//		 else 
//			 (*shiji_left_V)=left_ZhuanSu;
//		 
//		 if(right_ZhuanSu-(*shiji_right_V)>xiansu)
//			 (*shiji_right_V)+=xiansu;
//		 else if(right_ZhuanSu-(*shiji_right_V)<-xiansu)
//			 (*shiji_right_V)-=xiansu;
//		 else 
//			 (*shiji_right_V)=right_ZhuanSu;
//}
///*************************************************
//功能：跑直线AC
//参数：Angle旋转角度 0是往前 180是反转
//      Munber 非0请空标志位
//返回值：正常结束返回1，没结束返回0
//**************************************************/
//unsigned char First_Line(char Munber_AC, short Angle)
//{
//	static  long Pwm_Mun=0;
//	static unsigned char Start_flag=0;
//	if(Start_flag==0&&Munber_AC==0)
//	{
//		if(Pwm_Mun<35000)
//		{
//			Pwm_Mun+=right_cap;
//			motor_run_line(Yaw,start_Yaw-Angle,400);
//			motor_Left(PID_Increment(&pid_left,left_ZhuanSu,left_cap));//600
//			motor_Right(PID_Increment(&pid_right,right_ZhuanSu,right_cap));				
//		}
//		else if(Pwm_Mun>=35000)
//		{
//			if(temp_right_w==0x0000&&temp_left_w==0x0000)
//			{
//				Pwm_Mun+=right_cap;
//				motor_run_line(Yaw,start_Yaw-Angle,100);
//				motor_Left(PID_Increment(&pid_left,left_ZhuanSu,left_cap));//600
//				motor_Right(PID_Increment(&pid_right,right_ZhuanSu,right_cap));
//			}
//			else if((temp_right_w!=0x0000||temp_left_w!=0x0000)&&Pwm_Mun>=55000)
//			{
//					Start_flag=1;
//					Pwm_Mun=0;
//					return 1;
//			}
//		  }//Pwm_Mun<=45000
//	  }//Start_flag==0
//	if(Munber_AC==1)
//	{
//		Start_flag=0;
//	}
//	return 0;
//}
///*************************************************
//功能：跑斜直线
//参数：Angle第一个是37°第二个是141°，
//      Munber非0清空标志位
//返回值：正常结束返回1，没结束返回0
//**************************************************/
//unsigned char Blique_Line(short Angle,char Munber_AB)
//{
//	static  long Pwm_Mun_AB=0;
//	static unsigned char Start_flag=0;
//	float Targert=0,Targert2=0;
//	if(Start_flag==0&&Munber_AB==0)
//	{
//		if(Pwm_Mun_AB<1)//原地转
//		{
//            Pwm_Mun_AB=Turn_Place(Yaw,Angle);
//			motor_run_line(Yaw,start_Yaw-Angle,0);
//			motor_Left(PID_Increment(&pid_left,left_ZhuanSu,left_cap));//600
//			motor_Right(PID_Increment(&pid_right,right_ZhuanSu,right_cap));						
//		  }
//		  else if(Pwm_Mun_AB<45000)
//		  {
//			Pwm_Mun_AB+=right_cap;
//			motor_run_line(Yaw,start_Yaw-Angle,350);
//			motor_Left(PID_Increment(&pid_left,left_ZhuanSu,left_cap));//600
//			motor_Right(PID_Increment(&pid_right,right_ZhuanSu,right_cap));			 
//		  }
//		  else if(Pwm_Mun_AB>=45000)
//		  {
//			if(temp_right_w==0x0000&&temp_left_w==0x0000)
//			{
//				Pwm_Mun_AB+=right_cap;
//				motor_run_line(Yaw,start_Yaw-Angle,80);
//				motor_Left(PID_Increment(&pid_left,left_ZhuanSu,left_cap));//600
//				motor_Right(PID_Increment(&pid_right,right_ZhuanSu,right_cap));
//			}
//			else if((temp_right_w!=0x0000||temp_left_w!=0x0000)&&Pwm_Mun_AB>=45000)
//			{
//					Start_flag=1;
//					Pwm_Mun_AB=0;
//					return 1;
//			}				
//		  }//Pwm_Mun<=45000
//	  }//Start_flag==0
//	if(Munber_AB==1)
//	{
//		Start_flag=0;
//	}
//	return 0;
//}
///*************************************************
//功能：跑循迹BD
//参数：
//      Flag 0清空标志位,
//			1 第2/3题的第2个循迹
//			2是第2题的第1个循迹
//      Munber 非
//返回值：正常结束返回1，没结束返回0
//**************************************************/
//unsigned char Track_Line(char Flag)
//{
//	static long Pwm_Mun_BD=0;
//	static unsigned char Track_start_flag=0,run_mode_flag=0;
//	if(Track_start_flag==0)
//	{
//		run_mode_flag=Angle_Judge(Yaw,Flag);//run_mode_flag=2时给mpu
//		if(Pwm_Mun_BD<5000)
//		{
//			if(temp_right_w==0x0000&&temp_left_w==0x0000)//如果全部出线
//			{
//				motor_Left(PID_Increment(&pid_left,6,left_cap));//600
//				motor_Right(PID_Increment(&pid_right,0,right_cap));						
//			}
//			else if(temp_right_w!=0x0000||temp_left_w!=0x0000)
//			{
//				Pwm_Mun_BD+=right_cap;
//				motor_run_xunji(50,run_mode_flag);
//				motor_Left(PID_Increment(&pid_left,left_ZhuanSu,left_cap));//600
//				motor_Right(PID_Increment(&pid_right,right_ZhuanSu,right_cap));
//			}				
//		}
//		else if(Pwm_Mun_BD>=5000)
//		{
//			if(temp_right_w==0x0000&&temp_left_w==0x0000&&Pwm_Mun_BD<=45000)//如果全部出线
//			{
//					motor_Left(PID_Increment(&pid_left,600,left_cap));//600
//					motor_Right(PID_Increment(&pid_right,0,right_cap));
//			}
//			else if(temp_right_w!=0x0000||temp_left_w!=0x0000)
//			{
//				Pwm_Mun_BD+=right_cap;
//				motor_run_xunji(150,run_mode_flag);
//				motor_Left(PID_Increment(&pid_left,left_ZhuanSu,left_cap));//600
//				motor_Right(PID_Increment(&pid_right,right_ZhuanSu,right_cap));	
//			}
//			else if((temp_right_w==0x0000&&temp_left_w==0x0000)&&Pwm_Mun_BD>=45000)
//			{
//				if(motor_stop())
//				{
//					Track_start_flag=1;
//					Pwm_Mun_BD=0;
//					return 1;
//				}
//			}	
//		}//Pwm_Mun>=5000
//	}//Track_start_flag==0	
//	if(Flag==0)
//	{
//		Track_start_flag=0;
//	}
//	return 0;
//}
///*************************************************
//功能：跑循迹C
//参数：这个Flag只有3，是第三题的第一个循迹
//      Munber 0，
//      Munber 1或者非0，表示重复进入
//返回值：正常结束返回1，没结束返回0
//**************************************************/
//unsigned char Track2_Line(char Munber_C)
//{
//	static long Pwm_Mun_C=0;
//	static unsigned char Track2_start_flag=0,run_mode_flag=0;
//	if(Track2_start_flag==0&&Munber_C==0)
//	{
//		run_mode_flag=Angle_Judge(Yaw,3);//run_mode_flag=1时给mpu
//		if(Pwm_Mun_C<5000)
//		{
//			if(temp_right_w==0x0000&&temp_left_w==0x0000)//如果全部出线
//			{
//				motor_Left(PID_Increment(&pid_left,0,left_cap));//600
//				motor_Right(PID_Increment(&pid_right,600,right_cap));			
//			}
//			else
//			{
//				Pwm_Mun_C+=right_cap;
//				motor_run_xunji(40,run_mode_flag);
//				motor_Left(PID_Increment(&pid_left,left_ZhuanSu,left_cap));//600
//				motor_Right(PID_Increment(&pid_right,right_ZhuanSu,right_cap));	
//			}
//		}
//		else if(Pwm_Mun_C>=5000)
//		{
//			
//			if(temp_right_w==0x0000&&temp_left_w==0x0000&&Pwm_Mun_C<=45000)//如果全部出线
//			{
//				motor_Left(PID_Increment(&pid_left,0,left_cap));//600
//				motor_Right(PID_Increment(&pid_right,600,right_cap));			
//			}
//			else if(temp_right_w!=0x0000||temp_left_w!=0x0000)//只要左右循迹，有一个识别到就说明没出线
//			{
//				Pwm_Mun_C+=right_cap;
//				motor_run_xunji(150,0);
//				motor_Left(PID_Increment(&pid_left,left_ZhuanSu,left_cap));//600
//				motor_Right(PID_Increment(&pid_right,right_ZhuanSu,right_cap));	
//			}
//			else if((temp_right_w==0x0000||temp_left_w==0x0000)&&Pwm_Mun_C>=45000)
//			{
//				if(motor_stop())
//				{
//					Track2_start_flag=1;
//					Pwm_Mun_C=0;
//					return 1;
//				}
//			}				
//		}//Pwm_Mun>=5000
//	}//Track_start_flag==0
//	if(Munber_C==1)
//	{
//		Track2_start_flag=0;
//	}
//	return 0;
//}
///*************************************************
//功能：跑题目1
//参数：Clear等于0正常，Clear非0，重新清空标志位
//返回值：正常结束返回1，没结束返回0，清空标志位返回2
//**************************************************/
//unsigned char T_1(char Clear)//ok
//{
//	static unsigned char Run_Flag=0;
//	
//	if(Clear==1)//按键清空标志位
//	{
//		Run_Flag=0;
//		return 2;
//	}
//	if(Run_Flag==0&&Clear==0)
//	{
//		if(First_Line(0,0))
//		{
//			First_Line(1,0);
//			Run_Flag=1;
//			
//		}
//	}
//	else if(Run_Flag==1)
//	{
//		if(motor_stop())
//		{
//			Run_Flag=2;
//			return 1;
//		}
//	}
//	return 0;
//}
///*************************************************
//功能：跑题目2
//参数：Clear等于0正常，Clear非0，重新清空标志位
//返回值：正常结束返回1，没结束返回0，清空标志位返回2
//**************************************************/
//unsigned char T_2(char Clear_2)//ok
//{
//	static unsigned char Run_Flag=0;
//	
//	if(Clear_2==1)//按键清空
//	{
//		Run_Flag=0;
//		return 2;
//	}
//	
//	if(Run_Flag==0&&Clear_2==0)//第一次直线
//	{
//		if(First_Line(0,0))
//		{
//			First_Line(1,0);
//			Run_Flag=1;
//		}
//	}
//	else if(Run_Flag==1)//第一次循迹
//	{
//		if(Track_Line(2))
//		{
//			Track_Line(0);
//			Run_Flag=2;
//		}
//	}
//	else if(Run_Flag==2)//第二次直线
//	{
//		if(First_Line(0,180))
//		{
//			First_Line(1,180);
//			Run_Flag=3;		
//		}
//	}
//	else if(Run_Flag==3)//第二次循迹
//	{
//		if(Track_Line(1))
//		{
//			Track_Line(0);
//			Run_Flag=4;
//		}
//	}
//	else if(Run_Flag==4)
//	{
//		if(motor_stop())
//		{
//			Run_Flag=5;
//		}
//	}
//	return 0;
//}
///*************************************************
//功能：跑题目3
//参数：Clear等于0正常，Clear非0，重新清空标志位
//返回值：正常结束返回1，没结束返回0，清空标不反回值
//**************************************************/
//unsigned char T_3(char Clear)
//{
//	static unsigned char Run_Flag=0;
//	if(Clear==1)//按键清空
//	{
//		Run_Flag=0;	
//		return 2;		
//	}
//	if(Run_Flag==0)//第一个斜线
//	{
//		if(Blique_Line(37,0))
//		{
//			Blique_Line(37,1);
//			Run_Flag=1;
//		}
//	}
//	else if(Run_Flag==1)//第一个循迹
//	{
//		if(Track2_Line(0))
//		{
//			Track2_Line(1);
//			Run_Flag=2;
//		}
//	}
//	else if(Run_Flag==2)//第二个斜线
//	{
//		if(Blique_Line(143,0))
//		{
//			Blique_Line(143,1);
//			Run_Flag=3;
//		}
//	}
//	else if(Run_Flag==3)//第二个循迹
//	{
//		if(Track_Line(1))
//		{
//			Track_Line(0);
//			Run_Flag=4;
//		}
//	}
//	else if(Run_Flag==4&&Clear==3)
//	{
//		if(motor_stop())
//		{
//			Run_Flag=5;
//			return 1;//正常结束返回1
//		}
//	}
//	else if(Run_Flag==4&&Clear==0)
//	{
//		Run_Flag=5;
//		return 1;
//	}

//	return 0;
//}
///*************************************************
//功能：跑题目4
//参数：Clear等于0正常，Clear非0，重新清空标志位
//返回值：正常结束返回1，没结束返回0，清空标返回2
//**************************************************/
//unsigned char T_4(char Clear)
//{
//	static unsigned char Run_Flag=0,Return_Munber=1;
//	if(Clear==1)
//	{
//		Run_Flag=0;
//		return 1;
//	}
//	if(Return_Munber==1)
//	{
//		T_3(Return_Munber);
//		Return_Munber=0;
//	}
//	else
//	{
//		if(T_3(0)&&Run_Flag<4)
//		{
//			Return_Munber=1;
//			Run_Flag++;
//		}
//	}
//	return 0; 
//}
///************************************************
//功能：判断是否过这个点
//参数：当munber等于1时，Yaw是真实的mpu角度，Munber是我们要偏移的角度
//      当munber等于2时，
//**************************************************/
//float Count_Offset_Yaw(float set_offset_Yaw)
//{
//	float temp=0;
//	temp=Yaw+set_offset_Yaw;
//	if(temp>180)
//	{
//		return temp-360;
//	}
//	else if(temp<-180)
//	{
//		return temp+360;
//	}
//	
//	return temp;
//}


////unsigned char decision_mpu_or_xunji(float set_offset_Yaw)
////{
////	Start2=start_Yaw-180;//0
////		if(Start2>180)
////			Start2-=360;
////		else if(Start2<-180)
////			Start2+=360;
////		
////		Start1=Start2+20;//20
////		if(Start1>180)
////			Start1-=360;
////		else if(Start1<-180)
////			Start1+=360;
////		
////		if(start_Yaw>Yaw&&Start1<Yaw)
////			return 2;//给mpu
////		else
////			return 0;
////}
//unsigned char Angle_Judge(float Yaw,char Flag)
//{	
//	static float Start1=0,Start2=0;
//	if(Flag==1)//第二题第二个和第三题第二个循迹
//	{
//		Start2=start_Yaw-180;//0
//		if(Start2>180)
//			Start2-=360;
//		else if(Start2<-180)
//			Start2+=360;
//		
//		Start1=Start2+10;//20
//		if(Start1>180)
//			Start1-=360;
//		else if(Start1<-180)
//			Start1+=360;
//		
//		if(start_Yaw>Yaw&&Start1<Yaw)
//			return 2;//给mpu
//		else
//			return 0;
//	}
//	else if(Flag==2)//第二题第一个循迹
//	{
//		Start2=start_Yaw-180;
//		if(Start2>180)
//			Start2-=360;
//		if(Start2<-180)
//			Start2+=360;
//		
//		Start1=Start2-10;
//		if(Start1>180)
//			Start1-=360;
//		if(Start1<-180)
//			Start1+=360;
//		
//		if(start_Yaw>Yaw&&Start1<Yaw)
//			return 0;//给mpu
//		else
//			return 2;
//	}
//	else if(Flag==3)//第三第一弯道
//	{
//			Start1=start_Yaw-180;
//			if(Start1>180)
//				Start1-=360;
//			if(Start1<-180)
//				Start1+=360;
//				
//			Start2=start_Yaw-10;
//			if(Start2>180)
//				Start2-=360;
//			if(Start2<-180)
//				Start2+=360;
//			
//			if(Start2<Yaw&&Yaw<Start1)
//			{
//				return 0;
//			}
//			else
//			{
//				return 1;	
//			}
//	}

//	return 3;
//}	
///*************************************************
//功能：原地转
//参数：1是第一个A，2是第二个B
//**************************************************/
//unsigned char Turn_Place(float Yaw,short Angle)
//{
//	float Targert=0,Targert2=0;
//	if(Angle==37)
//	{
//		Targert=start_Yaw-Angle-5;
//		if(Targert>180)
//			Targert-=360;
//		if(Targert<-180)
//			Targert+=360;
//		
//		Targert2=start_Yaw-Angle+5;
//		if(Targert2>180)
//			Targert2-=360;
//		if(Targert2<-180)
//			Targert2+=360;
//		
//		if(Yaw<Targert2&&Yaw>Targert)
//			return 1;
//		else
//			return 0;	
//	}
//	else if(Angle==143)
//	{
//		Targert=start_Yaw+37-180+5;
//		if(Targert>180)
//			Targert-=360;
//		if(Targert<-180)
//			Targert+=360;
//		
//		Targert2=start_Yaw+37-180-5;
//		if(Targert2>180)
//			Targert2-=360;
//		if(Targert2<-180)
//			Targert2+=360;
//		
//		if(Yaw>Targert2&&Yaw<Targert)
//			return 1;
//		else
//			return 0;
//	}
//	return 0;
//}
//unsigned char Leave_Xunji(char Flag)
//{
//	if(temp_right_w==0x0000||temp_left_w==0x0000)
//	{
//		
//	}
//	return 0;
//}



/*
12200line1
循迹:右高位边，左低位边


*/

/**

BaiZheng 1右加 2左加
*/
/*************************************************
功能：原地转
参数：1是第一个A，2是第二个B

更改人：吴贵麒
建议：你原本注释是什么东西

改：*****************************************************
功能：判断车头是否转到位置

参数：Angle只能38，141（原作者写的可以考虑扩展）


返回：到达位置返回1

**************************************************/
unsigned char Turn_Place(short Angle)
{
	float Targert=0,Targert2=0;
	if(Angle==38)
	{
		Targert=start_Yaw-Angle-5;
		if(Targert>180)
			Targert-=360;
		if(Targert<-180)
			Targert+=360;
		
		Targert2=start_Yaw-Angle+5;
		if(Targert2>180)
			Targert2-=360;
		if(Targert2<-180)
			Targert2+=360;
		
		if(Yaw<Targert2&&Yaw>Targert)
			return 1;
		else
			return 0;	
	}
	else if(Angle==141)
	{
		Targert=start_Yaw-Angle+5;
		if(Targert>180)
			Targert-=360;
		if(Targert<-180)
			Targert+=360;
		
		Targert2=start_Yaw-Angle-5;
		if(Targert2>180)
			Targert2-=360;
		if(Targert2<-180)
			Targert2+=360;
		
		if(Yaw>Targert2&&Yaw<Targert)
			return 1;
		else
			return 0;
	}
	return 0;
}

/************************************************************

更改人：吴贵麒

能用：但有雷，参数问原作者：李，更改者无法讲清楚（）
motor_run_xunji 类 ：不同弯道用，temp_right，temp_left 给了速度差（快速弯道用）
***********************************************************/
void motor_run_xunji(unsigned short V,unsigned char BaiZheng)
{
	static unsigned short left_last=0,right_last=0;//上次巡线值
	static unsigned char qianhuan_falg=1;//回线标志
	short temp_left=0,temp_right=0,pid_out=0;
	if((temp_left_w!=0||temp_right_w!=0)&&qianhuan_falg)//有线
	{
		pid_out=PID_XunJi(&XunJi_error, BaiZheng);
		
		temp_left=V-(signed short)pid_out;
		temp_right=V*0.5+(signed short)pid_out;
		
		left_ZhuanSu=temp_left;
		right_ZhuanSu=temp_right;
		
		
		left_last=temp_left_w;
		right_last=temp_right_w;
    }
	else if ((temp_left_w==0&&temp_right_w==0))
	{
		qianhuan_falg=0;
	}
	
	if(qianhuan_falg==0)
	{
		if((temp_left_w&0xE000)||(temp_right_w&0x000E))
		{
			qianhuan_falg=1;
		}
		
		else 
		{
			if((left_last&0xffff)&&!(right_last&0xffff))//左边丢线,右没识别到线
			{
				right_ZhuanSu=300;
				left_ZhuanSu=0;
			}
			if(right_last&0xffff&&!(left_last&0xffff))//右边丢线,左没识别到线
			{
				right_ZhuanSu=0;
				left_ZhuanSu=300;
			}
//			else 
//			{
//				
//				if(BaiZheng==2)
//				{
//					right_ZhuanSu=0;
//					left_ZhuanSu=300;
//				}
//				
//			}
		}
		
	}
}



void motor_run_xunji2(unsigned short V,unsigned char BaiZheng)
{
	static unsigned short left_last=0,right_last=0;//上次巡线值
	static unsigned char qianhuan_falg=1;//回线标志
	short temp_left=0,temp_right=0,pid_out=0;
	if((temp_left_w!=0||temp_right_w!=0)&&qianhuan_falg)//有线
	{
		pid_out=PID_XunJi(&XunJi_error, BaiZheng);
		
		temp_left=V*0.5-(signed short)pid_out;
		temp_right=V+(signed short)pid_out;
		
		left_ZhuanSu=temp_left;
		right_ZhuanSu=temp_right;
		
		
		left_last=temp_left_w;
		right_last=temp_right_w;
    }
	else if ((temp_left_w==0&&temp_right_w==0))
	{
		qianhuan_falg=0;
	}
	
	if(qianhuan_falg==0)
	{
		if((temp_left_w&0xE000)||(temp_right_w&0x000E))
		{
			qianhuan_falg=1;
		}
		
		else 
		{
			if((left_last&0xffff)&&!(right_last&0xffff))//左边丢线,右没识别到线
			{
				right_ZhuanSu=300;
				left_ZhuanSu=0;
			}
			if(right_last&0xffff&&!(left_last&0xffff))//右边丢线,左没识别到线
			{
				right_ZhuanSu=0;
				left_ZhuanSu=300;
			}
			else 
			{
				
				if(BaiZheng==2)
				{
					right_ZhuanSu=0;
					left_ZhuanSu=300;
				}
			}
		}
		
	}
}


void motor_run_xunji3(unsigned short V,unsigned char BaiZheng)
{
	static unsigned short left_last=0,right_last=0;//上次巡线值
	static unsigned char qianhuan_falg=1;//回线标志
	short temp_left=0,temp_right=0,pid_out=0;
	if((temp_left_w!=0||temp_right_w!=0)&&qianhuan_falg)//有线
	{
		pid_out=PID_XunJi(&XunJi_error, BaiZheng);
		
		temp_left=V-(signed short)pid_out-800;
		temp_right=V+(signed short)pid_out;
		
		left_ZhuanSu=temp_left;
		right_ZhuanSu=temp_right;
		
		
		left_last=temp_left_w;
		right_last=temp_right_w;
    }
	else if ((temp_left_w==0&&temp_right_w==0))
	{
		qianhuan_falg=0;
	}
	
	if(qianhuan_falg==0)
	{
		if((temp_left_w&0xE000)||(temp_right_w&0x000E))
		{
			qianhuan_falg=1;
		}
		
		else 
		{
			if((left_last&0xffff)&&!(right_last&0xffff))//左边丢线,右没识别到线
			{
				right_ZhuanSu=300;
				left_ZhuanSu=0;
			}
			if(right_last&0xffff&&!(left_last&0xffff))//右边丢线,左没识别到线
			{
				right_ZhuanSu=0;
				left_ZhuanSu=300;
			}
			else 
			{
				
				if(BaiZheng==2)
				{
					right_ZhuanSu=0;
					left_ZhuanSu=300;
				}
			}
		}
		
	}
}


/****************************************************
赛道元素：

line1 A->B点
line2 C->D点
line3 A->C点
line4 B->D点

wandao2_1第二题第一个弯道
wandao3_2第三题第二个弯道
以此类推



****************************************************/

 long Pwm_add_number=0;
unsigned char line1()
{
	if(Pwm_add_number<90000)
	{
		Pwm_add_number+=left_cap;
		motor_run_line(start_Yaw,750);
		
	}
	else 
	{
		Pwm_add_number+=left_cap;
		motor_run_line(start_Yaw,480);
		if(temp_left_w!=0||temp_right_w!=0)//有线
		{
			kkkkkkkk=Pwm_add_number;
			Pwm_add_number=0;
			return 1;
			
		}
	}
	return 0;
}

unsigned char line2()
{
	if(Pwm_add_number<90000)
	{
		Pwm_add_number+=left_cap;
		motor_run_line(start_Yaw-180,450);
		
	}
	else 
	{
		Pwm_add_number+=left_cap;
		motor_run_line(start_Yaw-180,350);
		if(temp_left_w!=0||temp_right_w!=0)//有线
		{
			kkkkkkkk=Pwm_add_number;
			Pwm_add_number=0;
			return 1;
			
		}
	}
	return 0;
}
unsigned char line3()
{
	if(Pwm_add_number<1)
	{
		motor_run_line(start_Yaw-38,0);
		if(Turn_Place(38))
		{
			
			Pwm_add_number=1;
		}
	}
	else if(Pwm_add_number>0&&Pwm_add_number<130000)
	{
		Pwm_add_number+=left_cap;
		motor_run_line(start_Yaw-38,750);
		
	}
	else 
	{
		Pwm_add_number+=left_cap;
		motor_run_line(start_Yaw-38,450);
		if(temp_left_w!=0||temp_right_w!=0)//有线
		{
			kkkkkkkk=Pwm_add_number;
			Pwm_add_number=0;
			return 1;
			
		}
	}
	return 0;
}

unsigned char line4()
{
	if(Pwm_add_number<1)
	{
		motor_run_line(start_Yaw-141,0);
		if(Turn_Place(141))
		{
			
			Pwm_add_number=1;
		}
	}
	else if(Pwm_add_number>0&&Pwm_add_number<130000)
	{
		Pwm_add_number+=left_cap;
		motor_run_line(start_Yaw-141,750);
		
	}
	else 
	{
		Pwm_add_number+=left_cap;
		motor_run_line(start_Yaw-141,450);
		if(temp_left_w!=0||temp_right_w!=0)//有线
		{
			kkkkkkkk=Pwm_add_number;
			Pwm_add_number=0;
			return 1;
			
		}
	}
	return 0;
}

/*
函数名：wandao2_1()
功能：第二题弯道1
返回：出弯道 1

*/
unsigned char wandao2_1()
{
	unsigned char limit_Anger_flag=0; 
	short Start2=0,Start1=0;
	Start2=start_Yaw-180;
		if(Start2>180)
			Start2-=360;
		if(Start2<-180)
			Start2+=360;
		
		Start1=Start2-10;
		if(Start1>180)
			Start1-=360;
		if(Start1<-180)
			Start1+=360;
		
		if(start_Yaw>Yaw&&Start1<Yaw)//给MPU
			limit_Anger_flag=2;

	if(Pwm_add_number<5000)
	{
		Pwm_add_number+=left_cap;
		motor_run_xunji(650,limit_Anger_flag);
		
	}
	else if(Pwm_add_number>=5000&&Pwm_add_number<120000)
	{
		Pwm_add_number+=left_cap;
		motor_run_xunji(650,limit_Anger_flag);
		
		
	}
	if(Pwm_add_number>=120000)
	{
		if((temp_left_w!=0||temp_right_w!=0))
		{
			motor_run_xunji(500,limit_Anger_flag);
		}
		else
		{
			Pwm_add_number=0;
			return 1;
		}
	}
	return 0;
}

unsigned char wandao2_2()
{
	unsigned char limit_Anger_flag=0; 
	short Start2=0,Start1=0;
		Start2=start_Yaw-180;//0
		if(Start2>180)
			Start2-=360;
		else if(Start2<-180)
			Start2+=360;
		
		Start1=Start2+10;//20
		if(Start1>180)
			Start1-=360;
		else if(Start1<-180)
			Start1+=360;

		if(start_Yaw>Yaw&&Start1<Yaw)//给MPU
			limit_Anger_flag=2;
	if(Pwm_add_number<5000)
	{
		Pwm_add_number+=left_cap;
		motor_run_xunji(450,limit_Anger_flag);
		
	}
	else if(Pwm_add_number>=5000&&Pwm_add_number<120000)
	{
		Pwm_add_number+=left_cap;
		motor_run_xunji(450,limit_Anger_flag);
		
		
	}
	if(Pwm_add_number>=120000)
	{
		if((temp_left_w!=0||temp_right_w!=0))
		{
			motor_run_xunji(350,limit_Anger_flag);
		}
		else
		{
			Pwm_add_number=0;
			return 1;
		}
	}
	return 0;
}



unsigned char wandao3_1()
{
	unsigned char limit_Anger_flag=0; 
	short Start2=0,Start1=0;
		
			Start1=start_Yaw-180;
			if(Start1>180)
				Start1-=360;
			if(Start1<-180)
				Start1+=360;
				
			Start2=start_Yaw-10;
			if(Start2>180)
				Start2-=360;
			if(Start2<-180)
				Start2+=360;

		if(start_Yaw>Yaw&&Start1<Yaw)//给MPU
			limit_Anger_flag=1;
		
		
		Start1=start_Yaw-5+27;
		if(Start1>180)
			Start1-=360;
		if(Start1<-180)
			Start1+=360;
		
		Start2=start_Yaw+5+27;
		if(Start2>180)
			Start2-=360;
		if(Start2<-180)
			Start2+=360;
		
	if(Pwm_add_number<1)
	{
		motor_run_line(start_Yaw+27,0);
		if(Yaw<Start2&&Yaw>Start1)
		{
			Pwm_add_number=1;	
		}
	}
	else if(Pwm_add_number> 0&&Pwm_add_number<120000)
	{
		Pwm_add_number+=right_cap;
		motor_run_xunji2(670,limit_Anger_flag);
		
		
	}
	if(Pwm_add_number>=120000)
	{
		if((temp_left_w!=0||temp_right_w!=0))
		{
			motor_run_xunji2(480,limit_Anger_flag);
		}
		else
		{
			Pwm_add_number=0;
			return 1;
		}
	}
	return 0;
}


unsigned char wandao3_2()
{
	unsigned char limit_Anger_flag=0; 
	short Start2=0,Start1=0;
		
			Start1=start_Yaw-180;
			if(Start1>180)
				Start1-=360;
			if(Start1<-180)
				Start1+=360;
				
			Start2=start_Yaw-10;
			if(Start2>180)
				Start2-=360;
			if(Start2<-180)
				Start2+=360;

		if(start_Yaw>Yaw&&Start1<Yaw)//给mpu
			limit_Anger_flag=2;
		
		
		Start1=start_Yaw-5-27-180;
		if(Start1>180)
			Start1-=360;
		if(Start1<-180)
			Start1+=360;
		
		Start2=start_Yaw+5-27-180;
		if(Start2>180)
			Start2-=360;
		if(Start2<-180)
			Start2+=360;
		
	if(Pwm_add_number<1)
	{
		motor_run_line(start_Yaw-180-27,0);
		if(Yaw<Start2&&Yaw>Start1)
		{
			Pwm_add_number=1;	
		}
	}
	else if(Pwm_add_number> 0&&Pwm_add_number<120000)
	{
		Pwm_add_number+=left_cap;
		motor_run_xunji(670,limit_Anger_flag);
		
		
	}
	if(Pwm_add_number>=120000)
	{
		if((temp_left_w!=0||temp_right_w!=0))
		{
			motor_run_xunji(480,limit_Anger_flag);
		}
		else
		{
			Pwm_add_number=0;
			return 1;
		}
	}
	return 0;
}

void T1(unsigned char  run_flag)
{
	
	static char flag=0;
	if(run_flag==1)
	{
		if(flag==0)
		{
			if(line1())
			{
				flag=1;
			}
		}
		
		if (flag==1)
		{
			if(motor_stop())
			{
				PID_Init(&pid_left,6.0,0.015,2.0);//5.0,0.06,2.0
	      PID_Init(&pid_right,6.0,0.015,2.0);//5.0,0.06,2.0
				flag=2;
			}
		}
		
	}
	else if(run_flag==0)
	{
		flag=0;
	}
}
void T2(unsigned char  run_flag)
{
	static char flag=0;
	if(run_flag==1)
	{
		if(flag==0)
		{
			if(line1())
			{
				flag=1;
			}
		}
		else if(flag==1)
		{
			if(wandao2_1())
			{
				flag=2;
	
			}
		}
		else if(flag==2)
		{
			if(line2())
			{
				flag=3;
			}
		}
		
		else if(flag==3)
		{
			if(wandao2_2())
			{
				flag=4;
			}
		}
		else if(flag==4)
		{
			if(motor_stop())
			{
				flag=5;
				PID_Init(&pid_left,6.0,0.015,2.0);//5.0,0.06,2.0
				PID_Init(&pid_right,6.0,0.015,2.0);//5.0,0.06,2.0
			}
		}
	}
	else if(run_flag==0)
	{
		flag=0;
	}
}



#include <stdbool.h>
#include <math.h>  // 用于 fmod 和 fabs

// 归一化经度到 [0, 360)
static float normalize(float x) {
    float n = fmod(x, 360.0f);
    return n < 0.0f ? n + 360.0f : n;
}

// 判断点是否在区间线的左侧（start到end的顺时针方向为右侧，逆时针为左侧）
// 左侧定义：从start沿逆时针方向到end的区间内
bool is_on_left(float lon, float start, float end) {
    float s = normalize(start);
    float e = normalize(end);
    float p = normalize(lon);
    
    // 统一将区间调整为 start <= end 的形式（通过环形比较）
    if (s <= e) {
        // 不跨180°，左侧为 s <= p <= e
        return (p >= s && p <= e);
    } else {
        // 跨180°，左侧为 p >= s 或 p <= e（环形左侧）
        return (p >= s || p <= e);
    }
}

// 判断点是否在区间线的右侧（与左侧相反）
bool is_on_right(float lon, float start, float end) {
    return !is_on_left(lon, start, end);
}

unsigned char  T3(unsigned char  run_flag)
{
	static char flag=0;
	if(run_flag==1)
	{
		if(flag==0)
		{
			if(line3())
			{
				flag=1;
			}
		}
		else if(flag==1)
		{
			if(motor_stop())
			{
				flag=2;
				PID_Init(&pid_left,6.0,0.015,2.0);//5.0,0.06,2.0
				PID_Init(&pid_right,6.0,0.015,2.0);//5.0,0.06,2.0
			}
		}
		else if(flag==2)
		{
			if(wandao3_1())
			{
				flag=3;
			}
		}
		else if(flag==3)
		{
			if(motor_stop())
			{
				flag=4;
				PID_Init(&pid_left,6.0,0.015,2.0);//5.0,0.06,2.0
				PID_Init(&pid_right,6.0,0.015,2.0);//5.0,0.06,2.0
			}
		}
		else if(flag==4)
		{
			
			if(line4())
			{
				flag=5;
			}
		}
		else if(flag==5)
		{
			if(motor_stop())
			{
				flag=6;
				PID_Init(&pid_left,6.0,0.015,2.0);//5.0,0.06,2.0
				PID_Init(&pid_right,6.0,0.015,2.0);//5.0,0.06,2.0
			}
		}
		else if (flag==6)
		{
			if(wandao3_2())
			{
				flag=7;
			}
			
		}
		else if(flag==7)
		{
			if(motor_stop())
			{
				flag=8;
				PID_Init(&pid_left,6.0,0.015,2.0);//5.0,0.06,2.0
				PID_Init(&pid_right,6.0,0.015,2.0);//5.0,0.06,2.0
				return 1;
			}
			
		}
		
		
	}
	else if(run_flag==0)
	{
		flag=0;
	}
	return 0;
}

void T4(unsigned char  run_flag)
{
	static char flag=0;
	if(run_flag==1)
	{
		if(flag<4)
		{
			if(T3(1))
			{
				T3(0);
				flag++;
			}
		}
	}
	else if(run_flag==0)
	{
		flag=0;
	}
	
}