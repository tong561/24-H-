#include "xunji.h"

unsigned short temp_left_w=0,temp_right_w=0;//左右循迹值各16位
short WuCha_Munber=0;
unsigned short Temp_Left[16],Temp_Right[16];

/*************************************************

功能：读取循迹模块的值20ms进入

**************************************************/
unsigned char  Inrared_Get(void)
{
	    unsigned short temp_left=0,temp_right=0;
		unsigned char LED_Number=0;
		int i=0;
		CLR_left_SH;
	    CLR_right_SH;
		delay_cycles(80);
		SET_left_SH;
	    SET_right_SH;
		delay_cycles(80);		
		for(i=0; i<16; i++)
		{
			CLR_left_CL;
			CLR_right_CL;
			if(i!=0)
			{
				if(left_DA_GET()==1)
				{
					temp_left|=(0x01<<i);
					LED_Number++;
				}
			}
			if(i!=15)
			{
				if(right_DA_GET()==1)
				{
					temp_right|=(0x01<<i);
					LED_Number++;
				}
			}
			delay_cycles(80);
			SET_left_CL;
			SET_right_CL;
			delay_cycles(80);
		}
		temp_left_w=temp_left;//0000 0000 0000 0001
		temp_right_w=temp_right;//1000 0000 0000 0000
		return LED_Number;
}

/*************************************************************

功能：设置循迹模块的权重//左边第一个不要//右边最后一个不要
     1000 0000 0000 0000 | 0000 0000 0000 0001

设置：中间两个循迹权重是0，当识别到时不予理会，往两边权重慢慢加大
      权重越大，要转的角度就越大

**************************************************************/

//void XunJi_Jugde(void)
//{
//	WuCha_Munber=0;
//	for(int i=0;i<10;i++)
//	{
//		if(temp_left_w&0x01<<i)
//		{
//		  WuCha_Munber+=i*4;
//		}
//		if(temp_right_w&0x01<<i)
//		{
//		  WuCha_Munber-=i*4;
//		}
//	}

//}






