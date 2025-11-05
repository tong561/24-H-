#ifndef MY_PID_H
#define MY_PID_H
#include "main.h"


typedef struct 
{
	
    float Kp;
	float Ki;
	float Kd;   // PID参
    short error_j;     // 积分累计值
	short error;     //误差
	short error_last;//上次误差
	short error_Last_Last;//上上次误差
	int out_max;   // 输出限幅
	short Out_Pu;    //输出
} PID;


extern short P_out,I_out,D_out,erro;

void PID_Init(PID *pid, float Kp, float Ki, float Kd );
short PID_JiSuan(PID *pid, short setpoint,short newpoint) ;
short PID_Increment(PID *pid, short setpoint,short newpoint);
short PID_XunJi(PID *pid,unsigned char BaiZheng);
short Limit_Output(short value,  short max);
//void number_chuli(PID *pid,unsigned char *arr);
void Munber_Count(PID *pid,unsigned char *arr);
unsigned char write_String(float number, unsigned char buffer[40]);
unsigned char write_cann(int a,unsigned char  *buffer);
unsigned int Cube(unsigned int Cu,unsigned int Be);
short PID_Zhixian(PID *pid, float temp_YAW);

#endif 
