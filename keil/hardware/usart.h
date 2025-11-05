#ifndef _USART_H_
#define _USART_H_
#include "ti_msp_dl_config.h"
extern volatile unsigned char RX_ARR[40];
extern volatile unsigned short RX_jisu;


void usart_init(void);
void uart0_send_char(char ch);
void uart0_send_array(unsigned char *arr,int arr_size);
void uart0_send_string(char* str);
	
#endif
