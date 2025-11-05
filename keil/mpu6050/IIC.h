#ifndef __IIC_H_
#define __IIC_H_

#include "ti_msp_dl_config.h"

#define delay_us(x) delay_cycles(x*80)
#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif
#define my_delay_us(x) delay_cycles(x*80)
#define SDA_OUT()   {   DL_GPIO_initDigitalOutput(MPU6050_SDA_IOMUX);     \
                        DL_GPIO_setPins(MPU6050_PORT, MPU6050_SDA_PIN);    \
                        DL_GPIO_enableOutput(MPU6050_PORT, MPU6050_SDA_PIN); \
                    }
//设置SDA输入模式
#define SDA_IN()    { DL_GPIO_initDigitalInput(MPU6050_SDA_IOMUX); }

//获取SDA引脚的电平变化
#define SDA_GET()   ( ( ( DL_GPIO_readPins(MPU6050_PORT,MPU6050_SDA_PIN) & MPU6050_SDA_PIN ) > 0 ) ? 1 : 0 )

#define SCL_SET    DL_GPIO_setPins(MPU6050_PORT, MPU6050_CLK_PIN)
#define SCL_RESET  DL_GPIO_clearPins(MPU6050_PORT,MPU6050_CLK_PIN)//0

#define SDA_SET    DL_GPIO_setPins(MPU6050_PORT, MPU6050_SDA_PIN)
#define SDA_RESET  DL_GPIO_clearPins(MPU6050_PORT,MPU6050_SDA_PIN)//0

////IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 

unsigned char I2C_ReadOneByte(unsigned char I2C_Addr,unsigned char addr);
unsigned char IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data);
u8 IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data);
u8 IICwriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data);
u8 IICwriteBit(u8 dev,u8 reg,u8 bitNum,u8 data);
u8 IICreadBytes(u8 dev, u8 reg, u8 length, u8 *data);
void IIC_Sand(unsigned char data);
int i2cWrite(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data);
int i2cRead(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);


#endif
















