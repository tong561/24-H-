#include "Key.h"


/***********************************************************************************

 功能：按键单击

 参数：KeyMunber要传入的值

 返回：按下次数

***********************************************************************************/
unsigned char Key_Mnuber(void)
{
	static unsigned char start_flag=0,key=0,key_flag=0;
	if(((DL_GPIO_readPins(Key_Munber_PORT,Key_Munber_PIN_Key_PIN)&Key_Munber_PIN_Key_PIN)==0)&&start_flag<4)
	{
		start_flag++;
	}
	else if(((DL_GPIO_readPins(Key_Munber_PORT,Key_Munber_PIN_Key_PIN)&Key_Munber_PIN_Key_PIN)!=0)&&start_flag==4)
	{
		    key++;
			start_flag=0;
	}
	return key;
}
/***********************************************************************************

 功能：按键多击

 参数：KeyMunber要传入的值

 返回：按下次数

***********************************************************************************/
unsigned char Key_Mnuber_Hit(void)
{//start_flag进入中断次数 key返回按键值 test_munber多次点击时间长度
	static unsigned char start_flag=0,key_munber=0,test_munber=0,test_count=0;
	
	test_munber++;
	if(((DL_GPIO_readPins(Key_Munber_PORT,Key_Munber_PIN_Key_PIN)&Key_Munber_PIN_Key_PIN)==0)&&start_flag<4)
	{
		   start_flag++;
	}
	else if(((DL_GPIO_readPins(Key_Munber_PORT,Key_Munber_PIN_Key_PIN)&Key_Munber_PIN_Key_PIN)!=0)&&start_flag==4)
	{
		    test_count++;
			start_flag=0;
	}
	if(test_munber>250)
	{
		if(test_count>0)
		key_munber=test_count;
		test_count=0;
	  return key_munber;
	}
	else
	return key_munber;
}
unsigned char Key_Mune_duo(void)
{
	static unsigned char Key_Munber=0,Start_flag=0,Into_munber=0;
	unsigned char Keyber=0;
	Into_munber++;
	if(((DL_GPIO_readPins(Key_Munber_PORT,Key_Munber_PIN_Key_PIN)&Key_Munber_PIN_Key_PIN)==0)&&Start_flag<2)
	{
		Into_munber=0;
		Start_flag++;
	}
	else if(((DL_GPIO_readPins(Key_Munber_PORT,Key_Munber_PIN_Key_PIN)&Key_Munber_PIN_Key_PIN)!=0)&&Start_flag==2)
	{
		Start_flag=0;
		Into_munber=0;
		Key_Munber++;
	}
	if(Into_munber>60)
	{
		Into_munber=0;
		if(Key_Munber>0)
		Keyber=Key_Munber;
		Key_Munber=0;
		return Keyber;
	}
	else
	return 0;
}


