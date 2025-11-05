#ifndef _LCD_H
#define _LCD_H


#include "ti_msp_dl_config.h"

#define my_delay_ms(x) delay_cycles(x*80000)
#define USE_HORIZONTAL 1  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#define uint8_t 	unsigned  char 
#define uint16_t	unsigned short 
#define unint32_t	unsigned int   





#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif

#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 128
#endif

//color

#define COLORR_1 	0x0000  //白
#define COLORR_2 	0xFDB8  //浅粉红
#define COLORR_3 	0xfe19  //粉红
#define COLORR_4 	0xd8a7  //猩红
#define COLORR_5 	0xff9e  //脸红的淡紫色
#define COLORR_6 	0xdb92  //苍白的紫罗兰红色
#define COLORR_7 	0xf8b2  //深粉色
#define COLORR_8 	0xf81f  //灯笼海棠(紫红色)
#define COLORR_9 	0x8811  //深洋红色	
#define COLORR_10 0x8010  //紫色
#define COLORR_11 0xbaba  //适中的兰花紫
#define COLORR_12 0x901a  //深紫罗兰色
#define COLORR_13 0x9999  //深兰花紫

	
#define COLORG_1 0x2444		//森林绿
#define COLORG_2 0x7fe0		//查特酒绿
#define COLORG_3 0x2c4a 	//海洋绿
#define COLORG_4 0xafe5		//绿黄色

#define COLOR_RED  		0xf800
#define COLOR_GER 		0x07e0
#define COLOR_BRU 		0x001f
#define COLOR_BRE     0x0000
#define COLOR_WIR     0xFFFF

#define COL33 0xf800
#define COL32 0x07e0
#define COL31 0x001f

#define LCD_RES_Clr()  DL_GPIO_clearPins(LCD_PORT,LCD_LCD_RES_PIN)//RES
#define LCD_RES_Set()  DL_GPIO_setPins(LCD_PORT,LCD_LCD_RES_PIN)

#define LCD_DC_Clr()   DL_GPIO_clearPins(LCD_PORT,LCD_LCD_DC_PIN)//DC
#define LCD_DC_Set()   DL_GPIO_setPins(LCD_PORT,LCD_LCD_DC_PIN)

#define LCD_CS_Clr()   DL_GPIO_clearPins(LCD_PORT,LCD_LCD_CS_PIN)//CS
#define LCD_CS_Set()   DL_GPIO_setPins(LCD_PORT,LCD_LCD_CS_PIN)

#define LCD_BLK_Clr()  DL_GPIO_clearPins(LCD_PORT,LCD_LCD_BLK_PIN)//BLK
#define LCD_BLK_Set()  DL_GPIO_setPins(LCD_PORT,LCD_LCD_BLK_PIN)


void LCD_Init(void);
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
void LCD_ShowChar(u16 x,u16 y,u8 num,u16 fc,u16 bc,u8 sizey,u8 mode);
void LCD_ShowString(u16 x,u16 y,const char *p,u16 fc,u16 bc,u8 sizey,u8 mode);
//void LCD_ShowUnsignedIntNum(u16 x,u16 y,u16 num,u8 len,u16 fc,u16 bc,u8 sizey);
void LCD_ShowIntNum(u16 x,u16 y,u16 num,u8 len,u16 fc,u16 bc,u8 sizey);//+-
void My_LCD_ShowIntNum(u16 x,u16 y,u16 num,u16 fc,u16 bc,u8 sizey);
void LCD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey);
void LCD_Show_ErJinZhi(u16 x,u16 y,unsigned short num,u16 fc,u16 bc,u8 sizey);
void LCD_ShowUnsignedIntNum(u16 x,u16 y,u16 num,u8 len,u16 fc,u16 bc,u8 sizey);
#endif



