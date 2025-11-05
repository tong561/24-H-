#ifndef _xunji_H
#define _xunji_H
#include "ti_msp_dl_config.h"
//Left定义
#define SET_left_SH DL_GPIO_setPins(xun_ji_PORT, xun_ji_left_SH_PIN)
#define CLR_left_SH DL_GPIO_clearPins(xun_ji_PORT, xun_ji_left_SH_PIN)
#define SET_left_CL DL_GPIO_setPins(xun_ji_PORT, xun_ji_left_CL_PIN)
#define CLR_left_CL DL_GPIO_clearPins(xun_ji_PORT, xun_ji_left_CL_PIN)
#define left_DA_GET()   ( ( ( DL_GPIO_readPins(xun_ji_PORT,xun_ji_left_DA_PIN) & xun_ji_left_DA_PIN ) > 0 ) ? 1 : 0 )

//Right定义
#define SET_right_SH DL_GPIO_setPins(xun_ji_PORT, xun_ji_right_SH_PIN)
#define CLR_right_SH DL_GPIO_clearPins(xun_ji_PORT, xun_ji_right_SH_PIN)
#define SET_right_CL DL_GPIO_setPins(xun_ji_PORT, xun_ji_right_CL_PIN)
#define CLR_right_CL DL_GPIO_clearPins(xun_ji_PORT, xun_ji_right_CL_PIN)
#define right_DA_GET()   ( ( ( DL_GPIO_readPins(xun_ji_PORT,xun_ji_right_DA_PIN) & xun_ji_right_DA_PIN ) > 0 ) ? 1 : 0 )


extern unsigned short temp_left_w,temp_right_w;
extern  short WuCha_Munber;
unsigned char  Inrared_Get(void);
void XunJi_Jugde(void);
#endif 
