#include "LCD.h"
#include "lcdfornt.h"

#define  SPI_Sand8  LCD_Writ_Bus


/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(u8 dat)
{
    u8 recv_data = 0;

    LCD_CS_Clr();

    
    DL_SPI_transmitData8(SPI_1_INST, dat);
    
    while(DL_SPI_isBusy(SPI_1_INST));

    
    recv_data = DL_SPI_receiveData8(SPI_1_INST);
    
    while(DL_SPI_isBusy(SPI_1_INST));

    LCD_CS_Set();
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_CMD(unsigned char cmd)
{
	 LCD_DC_Clr();
	 SPI_Sand8(cmd);
	 LCD_DC_Set();
	
}

/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/

void LCD_WR_DATA(u16 Data)
{
	SPI_Sand8(Data>>8);
	SPI_Sand8(Data);
}

//void LCD_WR_DATA16(u16 Data)
//{
////	SPI_Sand16(Data);
//}
/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(u16 Data)
{
	SPI_Sand8(Data);
}

//void delay(int t)
//{
//	while(t--);
//}
/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
//void LCD_Writ_Bus(u8 dat) 
//{	
//  while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//检查接收标志位
//	SPI_I2S_SendData(SPI1,dat);
//	delay(1);
//}




/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
	if(USE_HORIZONTAL==0)
	{
		LCD_WR_CMD(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_CMD(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_CMD(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_WR_CMD(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_CMD(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_CMD(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_WR_CMD(0x2a);//列地址设置
		LCD_WR_DATA(x1+1);
		LCD_WR_DATA(x2+1);
		LCD_WR_CMD(0x2b);//行地址设置
		LCD_WR_DATA(y1+2);
		LCD_WR_DATA(y2+2);
		LCD_WR_CMD(0x2c);//储存器写
	}
	else
	{
		LCD_WR_CMD(0x2a);//列地址设置
		LCD_WR_DATA(x1+1);
		LCD_WR_DATA(x2+1);
		LCD_WR_CMD(0x2b);//行地址设置
		LCD_WR_DATA(y1+2);
		LCD_WR_DATA(y2+2);
		LCD_WR_CMD(0x2c);//储存器写
	}
}



void LCD_Init(void)
{
//	LCD_HW_Init();    //初始化SPI2
	LCD_RES_Clr();  //复位
	my_delay_ms(1000);
	LCD_RES_Set();
	my_delay_ms(100);
	
	LCD_BLK_Set();//打开背光
    my_delay_ms(100);
	LCD_CS_Clr();
	//************* Start Initial Sequence **********//
	LCD_WR_CMD(0x11); //Sleep out 
	my_delay_ms(120);              //Delay 120ms 
	//------------------------------------ST7735S Frame Rate-----------------------------------------// 
	LCD_WR_CMD(0xB1); 
	LCD_WR_DATA8(0x05); 
	LCD_WR_DATA8(0x3C); 
	LCD_WR_DATA8(0x3C); 
	LCD_WR_CMD(0xB2); 
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x3C); 
	LCD_WR_DATA8(0x3C); 
	LCD_WR_CMD(0xB3); 
	LCD_WR_DATA8(0x05); 
	LCD_WR_DATA8(0x3C); 
	LCD_WR_DATA8(0x3C); 
	LCD_WR_DATA8(0x05); 
	LCD_WR_DATA8(0x3C); 
	LCD_WR_DATA8(0x3C); 
	//------------------------------------End ST7735S Frame Rate---------------------------------// 
	LCD_WR_CMD(0xB4); //Dot inversion 
	LCD_WR_DATA8(0x03); 
	//------------------------------------ST7735S Power Sequence---------------------------------// 
	LCD_WR_CMD(0xC0); 
	LCD_WR_DATA8(0x28); 
	LCD_WR_DATA8(0x08); 
	LCD_WR_DATA8(0x04); 
	LCD_WR_CMD(0xC1); 
	LCD_WR_DATA8(0XC0); 
	LCD_WR_CMD(0xC2); 
	LCD_WR_DATA8(0x0D); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_CMD(0xC3); 
	LCD_WR_DATA8(0x8D); 
	LCD_WR_DATA8(0x2A); 
	LCD_WR_CMD(0xC4); 
	LCD_WR_DATA8(0x8D); 
	LCD_WR_DATA8(0xEE); 
	//---------------------------------End ST7735S Power Sequence-------------------------------------// 
	LCD_WR_CMD(0xC5); //VCOM 
	LCD_WR_DATA8(0x1A); 
	LCD_WR_CMD(0x36); //MX, MY, RGB mode 
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
	else LCD_WR_DATA8(0xA0); 
	//------------------------------------ST7735S Gamma Sequence---------------------------------// 
	LCD_WR_CMD(0xE0); 
	LCD_WR_DATA8(0x04); 
	LCD_WR_DATA8(0x22); 
	LCD_WR_DATA8(0x07); 
	LCD_WR_DATA8(0x0A); 
	LCD_WR_DATA8(0x2E); 
	LCD_WR_DATA8(0x30); 
	LCD_WR_DATA8(0x25); 
	LCD_WR_DATA8(0x2A); 
	LCD_WR_DATA8(0x28); 
	LCD_WR_DATA8(0x26); 
	LCD_WR_DATA8(0x2E); 
	LCD_WR_DATA8(0x3A); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x01); 
	LCD_WR_DATA8(0x03); 
	LCD_WR_DATA8(0x13); 
	LCD_WR_CMD(0xE1); 
	LCD_WR_DATA8(0x04); 
	LCD_WR_DATA8(0x16); 
	LCD_WR_DATA8(0x06); 
	LCD_WR_DATA8(0x0D); 
	LCD_WR_DATA8(0x2D); 
	LCD_WR_DATA8(0x26); 
	LCD_WR_DATA8(0x23); 
	LCD_WR_DATA8(0x27); 
	LCD_WR_DATA8(0x27); 
	LCD_WR_DATA8(0x25); 
	LCD_WR_DATA8(0x2D); 
	LCD_WR_DATA8(0x3B); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x01); 
	LCD_WR_DATA8(0x04); 
	LCD_WR_DATA8(0x13); 
	//------------------------------------End ST7735S Gamma Sequence-----------------------------// 
	LCD_WR_CMD(0x3A); //65k mode 
	LCD_WR_DATA8(0x05); 
	LCD_WR_CMD(0x29); //Display on 
	
}
/******************************************************************************
      函数说明：在指定区域填充颜色
      入口数据：xsta,ysta   起始坐标
                xend,yend   终止坐标
								color       要填充的颜色
      返回值：  无
******************************************************************************/
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 num;
	num=(xend-xsta)*(yend-ysta);
	LCD_Address_Set(xsta,ysta,xend-1,yend-1);//设置显示范围
//	SPI2->CR1|=1<<11;//设置SPI16位传输模式
//	SPI_Cmd(SPI2, ENABLE);//使能SPI
	while(num--)
	{
		SPI_Sand8(color>>8);
		SPI_Sand8(color);
		
//		while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET);
//		SPI2->DR=color;
//		SPI2->SR&=(1<<0);
//		while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_BSY)== SET);
//	}
//	SPI2->CR1=~SPI2->CR1;
//	SPI2->CR1|=1<<11;
//	SPI2->CR1=~SPI2->CR1;//设置SPI8位传输模式
//	SPI_Cmd(SPI2, ENABLE);//使能SPI
	}
}
/******************************************************************************
      函数说明：在指定位置画点
      入口数据：x,y 画点坐标
                color 点的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawPoint(unsigned char x,unsigned char y,unsigned int fc)
{
	LCD_Address_Set(x,y,x,y);
	LCD_WR_DATA(fc);

}
/******************************************************************************
      函数说明：显示单个字符
      入口数据：x,y显示坐标
                num 要显示的字符
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChar(u16 x,u16 y,u8 num,u16 fc,u16 bc,u8 sizey,u8 mode)
{
	u8 temp,sizex,t,m=0;
	u16 i,TypefaceNum;//一个字符所占字节大小
	u16 x0=x;
	sizex=sizey/2;
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
	num=num-' ';    //得到偏移后的值
	LCD_Address_Set(x,y,x+sizex-1,y+sizey-1);  //设置光标位置 
	for(i=0;i<TypefaceNum;i++)
	{ 
		if(sizey==12)temp=ascii_1206[num][i];		       //调用6x12字体
		else if(sizey==16)temp=ascii_1608[num][i];		 //调用8x16字体
		else return;
		for(t=0;t<8;t++)
		{
			if(!mode)//非叠加模式
			{
				if(temp&(0x01<<t))LCD_WR_DATA(fc);
				else LCD_WR_DATA(bc);
				m++;
				if(m%sizex==0)
				{
					m=0;
					break;
				}
			}
			else//叠加模式
			{
				if(temp&(0x01<<t))LCD_DrawPoint(x,y,fc);//画一个点
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
			}
		}
	}   	 	  
}
/******************************************************************************
      函数说明：显示字符串
      入口数据：x,y显示坐标
                *p 要显示的字符串
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowString(u16 x,u16 y,const char *p,u16 fc,u16 bc,u8 sizey,u8 mode)
{         
	while(*p!='\0')
	{       
		LCD_ShowChar(x,y,*p,fc,bc,sizey,mode);
		x+=sizey/2;
		p++;
	}  
}
/******************************************************************************
      函数说明：显示数字
      入口数据：m底数，n指数
      返回值：  无
******************************************************************************/
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;
	return result;
}

unsigned char Get_num_len(u32 num)
{
	u32 C_temp=10;
	unsigned char len=1;
	while(num/C_temp)
	{
		C_temp*=10;
		len++;
	}
	return len;
}
/******************************************************************************
      函数说明：显示整数变量
      入口数据：x,y显示坐标
                num 要显示整数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void LCD_ShowUnsignedIntNum(u16 x,u16 y,u16 num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	u8 t,temp;
	u8 enshow=0;
	u8 sizex=sizey/2;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
} 
void LCD_ShowIntNum(u16 x,u16 y,u16 num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	if(num&0x8000)
	{
		LCD_ShowChar(x,y,'-',fc,bc,sizey,0);
		LCD_ShowUnsignedIntNum(x+sizey/2,y,(~(num-1))&0x0000ffff,len,fc,bc,sizey);
		
	}
	else
	{
		LCD_ShowChar(x,y,'+',fc,bc,sizey,0);
		LCD_ShowUnsignedIntNum(x+sizey/2,y,num,len,fc,bc,sizey);
	}
//	
} 

void My_LCD_ShowIntNum(u16 x,u16 y,u16 num,u16 fc,u16 bc,u8 sizey)
{         	
	u8 t,temp;
	u8 enshow=0;
	u8 sizex=sizey/2;
	u8 len= Get_num_len(num);
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
} 
void LCD_ShowuFloatNum1(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	u8 t,temp,sizex;
	int num1;
	sizex=sizey/2;
	if(num<0)
	{
		num=-num;
	}
	num1=num*100;
	for(t=0;t<len;t++)
	{
		temp=(num1/mypow(10,len-t-1))%10;
		if(t==(len-2))
		{
			LCD_ShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey,0);
			t++;
			len+=1;
		}
		LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
	
}

void LCD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey)
{
	if(num<0)
	{
		LCD_ShowChar(x,y,'-',fc,bc,sizey,0);
		LCD_ShowuFloatNum1(x+sizey/2,y,num,len, fc, bc, sizey);
	}
	else
	{
		LCD_ShowChar(x,y,'+',fc,bc,sizey,0);
		LCD_ShowuFloatNum1(x+sizey/2,y,num,len, fc, bc, sizey);
	}
}
/*******************************************
功能：显示二进制

*******************************************/

void LCD_Show_ErJinZhi(u16 x,u16 y,unsigned short num,u16 fc,u16 bc,u8 sizey)
{
	u16 x_temp=x;
	for(unsigned char i=0;i<16;i++)
	{
		if((num&(0x01<<i))!=0)
		{
			LCD_ShowChar(x_temp,y,'1',fc,bc,sizey,0);
			
		}
		else
		{
			LCD_ShowChar(x_temp,y,'0',fc,bc,sizey,0);
		}
		x_temp+=sizey/2;
	}
}
	