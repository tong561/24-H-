/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/********************************

弯道=12000

直线=12000

斜线=12000





**********************************/
#include "ti_msp_dl_config.h"
#include "LCD.h"
#include "PID.h"
#include "motor.h"
#include "usart.h"
#include "MPU6050.h"
#include "xunji.h"
#include "stdio.h"
#include <ti/iqmath/include/IQmathLib.h>
#include "Key.h"
#include "main.h"
#define right_A TIMG12->COUNTERREGS.CTR//a31
#define right_B TIMG8->COUNTERREGS.CTR//A01
#define left_A TIMA1->COUNTERREGS.CTR//A28
#define left_B TIMA0->COUNTERREGS.CTR//A00
unsigned char LED_Num=0;

static unsigned char Mode_Munber_Flag=0;//模式标志位
short left_cap=0;//左边捕获
short right_cap=0;//右边捕获
float Pitch= 0;
float Roll = 0;
float Yaw  = 0;//mpu的值
unsigned char MPUOK_flag=0;//mpu开始标志位
unsigned short MPU_ZhunBei_jisu=0;//mpu计数
 long kkkkkkkk=0;
 
 
/**************************************

main 函数流程图

开始

外设初始化

显示蓝色背景

等待MPU6050初始化完成

显示绿色背景

执行显示任务

**************************************/
 
int main(void)
{
  SYSCFG_DL_init();
	usart_init();
	LCD_Init();
	LCD_Fill(0,0,LCD_W,LCD_H,0x00F8);
	NVIC_EnableIRQ(MPU6050_INT_IRQN);//mpu外部中断
	PID_Init(&pid_left,6.0,0.015,2.0);//5.0,0.06,2.0
	PID_Init(&pid_right,6.0,0.015,2.0);//5.0,0.06,2.0
	PID_Init(&XunJi_error,4*4,0.0,0.5);
	PID_Init(&Zhixian,3.5,0.0,1.0);//5.0,0.0,1.0
	uart0_send_char('a');
	MPU6050_initialize();
	DMP_Init();
	//MPU6050_INT_Ini();
    while (1) 
		{
			if(MPUOK_flag==1)//MPU就绪开始
			{
				MPUOK_flag=0;
				DL_TimerG_startCounter(PWM_0_INST);//PWM开始输出
				DL_TimerG_startCounter(TIMER_0_INST);
				NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);//使能G6定时中断
				NVIC_EnableIRQ(TIMER_1_INST_INT_IRQN);//使能G6定时中断
				LCD_Fill(0,0,LCD_W,LCD_H,0x0780);
				
				DL_GPIO_clearPins(motor_PORT,motor_left_2_PIN);//行驶方向
				DL_GPIO_setPins  (motor_PORT,motor_left_1_PIN);
				
				DL_GPIO_clearPins(motor_PORT,motor_right_1_PIN);
				DL_GPIO_setPins  (motor_PORT,motor_right_2_PIN);
			}
			//修改pid
			//Munber_Count(&XunJi_error,(unsigned char *)RX_ARR);
			
			LCD_ShowFloatNum1(0,0, Zhixian.Kp,5,0x0000,0xffff,12);
			LCD_ShowIntNum(60,0, Mode_Munber_Flag,5,0x0000,0xffff,12);//按键次数
			
			LCD_ShowFloatNum1(0,12,Zhixian.Ki,5,0x0000,0xffff,12);
			LCD_ShowFloatNum1(0,24,Zhixian.Kd,5,0x0000,0xffff,12);
			LCD_ShowChar(48,0, 'P',0x0000,0xffff,12,0);
			LCD_ShowChar(48,12,'I',0x0000,0xffff,12,0);
			LCD_ShowChar(48,24,'D',0x0000,0xffff,12,0);
			LCD_ShowIntNum(0,36,pid_left.Out_Pu,5,0x0000,0xffff,12);
			LCD_ShowString(60,36,"le_O:",0x0000,0xffff,12,1);
			LCD_ShowString(0,84,"Yaw  :",0x0000,0xffff,12,1);
			LCD_ShowFloatNum1(36,84,Yaw,7,0x0000,0xffff,12);
			LCD_ShowString(0,96,"StartYaw:",0x0000,0xffff,12,1);
			LCD_ShowFloatNum1(48,96,start_Yaw,7,0x0000,0xffff,12);
			LCD_ShowIntNum(0,148,MPU_ZhunBei_jisu,5,0x0000,0xffff,12);
			LCD_Show_ErJinZhi(0,108,temp_left_w,0x0000,0xffff,12);
			LCD_Show_ErJinZhi(0,120,temp_right_w,0x0000,0xffff,12);
			
			LCD_ShowIntNum(0,60,right_cap,7,0xf800,0xffff,12);
			LCD_ShowIntNum(0,72,left_cap,7,0xf800,0xffff,12);
			printf("%d,%d,%d,%d,%d,%d\n",left_ZhuanSu,right_ZhuanSu,left_cap,right_cap,pid_left.Out_Pu,(int)kkkkkkkk);
		}
}


/**********************************
TIMG6_IRQHandler 中断服务函数流程图（最高优先级）

定时2.5ms

记录捕获值

无异常更新电机控制


参数：
带temp(一些临时变量，用于尽快完成寄存器等的读取，防止干扰下次计数)

left_A left_B right_B right_A:定时器CTR寄存器（计数寄存器）

right_cap left_cap 左右捕获值（经过低通滤波）

left_ZhuanSu 左轮转速 （<=-2000为异常值（用于电机刹车））


***********************************/

void TIMG6_IRQHandler()//定时2.5ms中断
{

	static short time =0,temp_right_AB=0,temp_left_AB=0;
	static short  shiji_left_V=0,shiji_right_V=0,last_left_cap=0,last_right_cap=0,left_cap1=0,left_cap2=0;
	  if (DL_TimerG_getPendingInterrupt(TIMER_0_INST)==DL_TIMER_IIDX_ZERO)
	  {
			
			temp_right_AB=right_A+right_B;
			temp_left_AB=left_A +left_B;
			
			if(Direction_right_flag)
			{
				right_cap=(((short)(temp_right_AB))>>2)+right_cap*0.75;//简单低通滤波了
				
			}
			else
			{
				right_cap=-(((short)(temp_right_AB))>>2)+right_cap*0.75;
			}
			if(Direction_left_flag)
			{
				left_cap=(((short)(temp_left_AB))>>2)+left_cap*0.75;	
			}
			else
			{
				left_cap=-(((short)(temp_left_AB))>>2)+left_cap*0.75;
			}
			
			
			left_A=0;
			left_B=0;
			right_A=0;
			right_B=0;
			if(left_ZhuanSu>-2000)//刷新控制状态
			{
				motor_Left(PID_Increment(&pid_left,left_ZhuanSu,left_cap));//600
				motor_Right(PID_Increment(&pid_right,right_ZhuanSu,right_cap));
			}
	 }
}


/**********************************
TIMG0_IRQHandler 中断服务函数流程图（次高优先级）

定时5ms

读取键值,跟新循迹状态

根据键值执行题目





参数：
Key_Munber_Flag 键值
Mode_Munber_Flag 执行模式标志
LED_Num 全局且可外部调用 循迹灭灯的个数（有线灭）

***********************************/
void TIMG0_IRQHandler()
{
	static short jisu_flag=0;
	static unsigned char  Key_Munber_Flag=0;//按键次数标志位
		if (DL_TimerG_getPendingInterrupt(TIMER_1_INST)==DL_TIMER_IIDX_ZERO)
		{
		
		 Key_Munber_Flag=Key_Mune_duo();//读键值
			switch(Key_Munber_Flag)//根据键值判断执行模式
			{
				case 1:
					Mode_Munber_Flag=1;
					PID_Init(&pid_left,6.0,0.015,2.0);//5.0,0.06,2.0
					PID_Init(&pid_right,6.0,0.015,2.0);//5.0,0.06,2.0
			    break;
				case 2:
					Mode_Munber_Flag=2;
					PID_Init(&pid_left,6.0,0.015,2.0);//5.0,0.06,2.0
					PID_Init(&pid_right,6.0,0.015,2.0);//5.0,0.06,2.0
			    break;
				case 3:
				  Mode_Munber_Flag=3;
					PID_Init(&pid_left,6.0,0.015,2.0);//5.0,0.06,2.0
					PID_Init(&pid_right,6.0,0.015,2.0);//5.0,0.06,2.0
			    break;
				case 4:
				  Mode_Munber_Flag=4;
					PID_Init(&pid_left,6.0,0.015,2.0);//5.0,0.06,2.0
					PID_Init(&pid_right,6.0,0.015,2.0);//5.0,0.06,2.0
					break;
				case 5:
					PID_Init(&pid_left,6.0,0.015,2.0);//5.0,0.06,2.0
					PID_Init(&pid_right,6.0,0.015,2.0);//5.0,0.06,2.0
				  Mode_Munber_Flag=5;
			    break;
				default:	
					break;
		}
		//读循迹模块
		LED_Num=Inrared_Get();
		
	
		if(Mode_Munber_Flag==1)
			T1(1);
		else if(Mode_Munber_Flag==2)
			
			T2(1);
		else if(Mode_Munber_Flag==3)
			T3(1);
		else if(Mode_Munber_Flag==4)
			T4(1);
		else if(Mode_Munber_Flag==5)
		{
			
			T1(0);
			T2(0);
			T3(0);
			T4(0);
			
			//清除pid积分（重新初始化）
			left_ZhuanSu=-2000;
			PID_Init(&pid_left,6.0,0.015,2.0);//5.0,0.06,2.0
    	PID_Init(&pid_right,6.0,0.015,2.0);//5.0,0.06,2.0
			//停车恢复默认工作状态
			DL_TimerG_setCaptureCompareValue(MOTOR_PWM_INST,0,MOTOR_LEFT_IDX);//left
		  DL_TimerG_setCaptureCompareValue(MOTOR_PWM_INST,0,MOTOR_RIGHT_IDX);//right
			DL_GPIO_clearPins(motor_PORT,motor_left_2_PIN);//行驶方向正转
		  DL_GPIO_setPins  (motor_PORT,motor_left_1_PIN);		
		  DL_GPIO_clearPins(motor_PORT,motor_right_1_PIN);
			DL_GPIO_setPins  (motor_PORT,motor_right_2_PIN);
			Mode_Munber_Flag=0;
		}
	 }
}
/*************************************************
GROUP1_IRQHandler  外部中断

更新MPU6050


*************************************************/


void GROUP1_IRQHandler()
{
	static  float  Fir_Yaw,Average_Error;
	static  short  Less=0;
	float cpu_time_used;
	uint32_t x=0;
	x=DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1);
	
	if(x==MPU6050_INT_IIDX)
	{
		Read_DMP_Correct_error_data(&Pitch,&Roll,&Yaw,&MPUOK_flag,&MPU_ZhunBei_jisu);
	}
}




