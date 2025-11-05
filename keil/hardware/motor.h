#ifndef _MOTOR_H
#define _MOTOR_H

#include "ti_msp_dl_config.h"
#include "pid.h"
#include "xunji.h"
#include "mpu6050.h"
#include "main.h"
#include "usart.h"
#include "stdio.h"
//PWM端口定义
#define MOTOR_PWM_INST PWM_0_INST
#define MOTOR_LEFT_IDX  GPIO_PWM_0_C0_IDX
#define MOTOR_RIGHT_IDX GPIO_PWM_0_C1_IDX
 #define xiansu 1000
extern  PID pid_left;
extern PID pid_right;
extern PID XunJi_error;
extern PID Zhixian;
extern short test_left,test_right;
extern signed short left_ZhuanSu,right_ZhuanSu;//左右转速
extern float start_Yaw;
extern unsigned char Direction_right_flag,Direction_left_flag;
//extern float app;
//函数
//void motor_Left( short PWM);
//void motor_Right(short PWM);
//void  motor_run_line(float qidai_Yaw,unsigned short V);
//void motor_run_xunji(unsigned short V,unsigned char BaiZheng);
//unsigned char motor_stop(void);
//void  XianSu_Judge(short * shiji_left_V,short * shiji_right_V );
//unsigned char Angle_Judge(float Yaw,char Flag);
//unsigned char Turn_Place(float Yaw,short Angle);
//unsigned char Track_Line(char Flag);//循迹
//unsigned char First_Line(char Munber,short Angle);//直线
//unsigned char Blique_Line(short Angle,char Munber);//斜线
//unsigned char T_1(char Clear);
//unsigned char T_2(char Clear);
//unsigned char T_3(char Clear);
//unsigned char T_4(char Clear);
void motor_Left( short PWM);
void motor_Right( short PWM);
void T1(unsigned char  run_flag);
void T2(unsigned char  run_flag);
unsigned char T3(unsigned char  run_flag);
void T4(unsigned char  run_flag);
	
#endif 

