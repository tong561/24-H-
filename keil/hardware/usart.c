#include "usart.h"
#include "stdio.h"

//volatile unsigned int delay_times = 0 ;
//volatile unsigned char uart_data = 0 ;
////volatile char usart_receive_flag=0;
volatile unsigned char RX_ARR[40];
volatile unsigned short RX_jisu=0;
void usart_init(void)
{
	//清除串口中断标志
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
	//使能串口中断
	NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

//printf("Board Init [[ ** LCKFB ** ]]\r\n");
}
/***********************************************************************************

 功能：串口发送单个字符

 参数：ch要发送的字符

***********************************************************************************/
void uart0_send_char(char ch)
{
	//当串口0忙的时候等待，不忙的时候再发送传进来的字符
	while( DL_UART_isBusy(UART_0_INST) == true );
	//发送单个字符
	DL_UART_Main_transmitData(UART_0_INST, ch);

}

/***********************************************************************************

 功能：串口发送数组

 参数：arr要发送的数组，arr_size发送的数组位数

***********************************************************************************/
void uart0_send_array(unsigned char *arr,int arr_size)
{
	//遍历数组，逐个发送
	for(int i=0;i<arr_size;i++)
	{
		uart0_send_char(arr[i]);
	}
}

/***********************************************************************************

 功能：串口发送字符串

 参数：str要发送的字符串

***********************************************************************************/
void uart0_send_string(char* str)
{
	//当前字符串地址不在结尾 并且 字符串首地址不为空
	while(*str!=0&&str!=0)
	{
		//发送字符串首地址中的字符，并且在发送完成之后首地址自增
		uart0_send_char(*str++);
	}
}


/***********************************************************************************

 功能：printf函数重定义

 参数：ch字符串，FILE *stream文件流指针

***********************************************************************************/
#if !defined(__MICROLIB)
//不使用微库的话就需要添加下面的函数
#if (__ARMCLIB_VERSION <= 6000000)
//如果编译器是AC5  就定义下面这个结构体
struct __FILE
{
	int handle;
};
#endif

FILE __stdout;

//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}
#endif

//printf函数重定义
int fputc(int ch, FILE *stream)
{
	//当串口0忙的时候等待，不忙的时候再发送传进来的字符
	while( DL_UART_isBusy(UART_0_INST) == true );
	
	DL_UART_Main_transmitData(UART_0_INST, ch);
	
	return ch;
}






void UART0_IRQHandler()//串口中断
{
	static unsigned short RX_jisu_static=0;
	static unsigned char Rx_Data=0;
	if(DL_UART_getPendingInterrupt(UART_0_INST)==DL_UART_IIDX_RX)
	{
			Rx_Data=DL_UART_Main_receiveData(UART_0_INST);
			RX_ARR[RX_jisu_static]=Rx_Data;
			RX_jisu_static++;
			if(RX_jisu_static>=40)
			{
				RX_jisu=RX_jisu_static;
				RX_jisu_static=0;
			}
			if(Rx_Data=='\n')
			{
				RX_jisu=RX_jisu_static;
				RX_jisu_static=0;
			}
	}
}



