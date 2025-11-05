/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define CPUCLK_FREQ                                                     80000000



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMG7
#define PWM_0_INST_IRQHandler                                   TIMG7_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMG7_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                             20000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOB
#define GPIO_PWM_0_C0_PIN                                         DL_GPIO_PIN_15
#define GPIO_PWM_0_C0_IOMUX                                      (IOMUX_PINCM32)
#define GPIO_PWM_0_C0_IOMUX_FUNC                     IOMUX_PINCM32_PF_TIMG7_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_0_C1_PORT                                                 GPIOB
#define GPIO_PWM_0_C1_PIN                                         DL_GPIO_PIN_16
#define GPIO_PWM_0_C1_IOMUX                                      (IOMUX_PINCM33)
#define GPIO_PWM_0_C1_IOMUX_FUNC                     IOMUX_PINCM33_PF_TIMG7_CCP1
#define GPIO_PWM_0_C1_IDX                                    DL_TIMER_CC_1_INDEX



/* Defines for right_CAP_A */
#define right_CAP_A_INST                                                (TIMG12)
#define right_CAP_A_INST_IRQHandler                            TIMG12_IRQHandler
#define right_CAP_A_INST_INT_IRQN                              (TIMG12_INT_IRQn)
/* GPIO defines for channel 1 */
#define GPIO_right_CAP_A_C1_PORT                                           GPIOA
#define GPIO_right_CAP_A_C1_PIN                                   DL_GPIO_PIN_31
#define GPIO_right_CAP_A_C1_IOMUX                                 (IOMUX_PINCM6)
#define GPIO_right_CAP_A_C1_IOMUX_FUNC               IOMUX_PINCM6_PF_TIMG12_CCP1

/* Defines for right_CAP_B */
#define right_CAP_B_INST                                                 (TIMG8)
#define right_CAP_B_INST_IRQHandler                             TIMG8_IRQHandler
#define right_CAP_B_INST_INT_IRQN                               (TIMG8_INT_IRQn)
/* GPIO defines for channel 0 */
#define GPIO_right_CAP_B_C0_PORT                                           GPIOA
#define GPIO_right_CAP_B_C0_PIN                                    DL_GPIO_PIN_1
#define GPIO_right_CAP_B_C0_IOMUX                                 (IOMUX_PINCM2)
#define GPIO_right_CAP_B_C0_IOMUX_FUNC                IOMUX_PINCM2_PF_TIMG8_CCP0

/* Defines for left_CAP_A */
#define left_CAP_A_INST                                                  (TIMA1)
#define left_CAP_A_INST_IRQHandler                              TIMA1_IRQHandler
#define left_CAP_A_INST_INT_IRQN                                (TIMA1_INT_IRQn)
/* GPIO defines for channel 0 */
#define GPIO_left_CAP_A_C0_PORT                                            GPIOA
#define GPIO_left_CAP_A_C0_PIN                                    DL_GPIO_PIN_28
#define GPIO_left_CAP_A_C0_IOMUX                                  (IOMUX_PINCM3)
#define GPIO_left_CAP_A_C0_IOMUX_FUNC                 IOMUX_PINCM3_PF_TIMA1_CCP0

/* Defines for left_CAP_B */
#define left_CAP_B_INST                                                  (TIMA0)
#define left_CAP_B_INST_IRQHandler                              TIMA0_IRQHandler
#define left_CAP_B_INST_INT_IRQN                                (TIMA0_INT_IRQn)
/* GPIO defines for channel 0 */
#define GPIO_left_CAP_B_C0_PORT                                            GPIOA
#define GPIO_left_CAP_B_C0_PIN                                     DL_GPIO_PIN_0
#define GPIO_left_CAP_B_C0_IOMUX                                  (IOMUX_PINCM1)
#define GPIO_left_CAP_B_C0_IOMUX_FUNC                 IOMUX_PINCM1_PF_TIMA0_CCP0




/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMG6)
#define TIMER_0_INST_IRQHandler                                 TIMG6_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG6_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                          (2499U)
/* Defines for TIMER_1 */
#define TIMER_1_INST                                                     (TIMG0)
#define TIMER_1_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_1_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_1_INST_LOAD_VALUE                                         (24999U)



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                           40000000
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_40_MHZ_115200_BAUD                                      (21)
#define UART_0_FBRD_40_MHZ_115200_BAUD                                      (45)




/* Defines for SPI_1 */
#define SPI_1_INST                                                         SPI1
#define SPI_1_INST_IRQHandler                                   SPI1_IRQHandler
#define SPI_1_INST_INT_IRQN                                       SPI1_INT_IRQn
#define GPIO_SPI_1_PICO_PORT                                              GPIOB
#define GPIO_SPI_1_PICO_PIN                                       DL_GPIO_PIN_8
#define GPIO_SPI_1_IOMUX_PICO                                   (IOMUX_PINCM25)
#define GPIO_SPI_1_IOMUX_PICO_FUNC                   IOMUX_PINCM25_PF_SPI1_PICO
#define GPIO_SPI_1_POCI_PORT                                              GPIOB
#define GPIO_SPI_1_POCI_PIN                                      DL_GPIO_PIN_21
#define GPIO_SPI_1_IOMUX_POCI                                   (IOMUX_PINCM49)
#define GPIO_SPI_1_IOMUX_POCI_FUNC                   IOMUX_PINCM49_PF_SPI1_POCI
/* GPIO configuration for SPI_1 */
#define GPIO_SPI_1_SCLK_PORT                                              GPIOB
#define GPIO_SPI_1_SCLK_PIN                                       DL_GPIO_PIN_9
#define GPIO_SPI_1_IOMUX_SCLK                                   (IOMUX_PINCM26)
#define GPIO_SPI_1_IOMUX_SCLK_FUNC                   IOMUX_PINCM26_PF_SPI1_SCLK



/* Port definition for Pin Group Key_Munber */
#define Key_Munber_PORT                                                  (GPIOA)

/* Defines for PIN_Key: GPIOA.16 with pinCMx 38 on package pin 9 */
#define Key_Munber_PIN_Key_PIN                                  (DL_GPIO_PIN_16)
#define Key_Munber_PIN_Key_IOMUX                                 (IOMUX_PINCM38)
/* Port definition for Pin Group LCD */
#define LCD_PORT                                                         (GPIOB)

/* Defines for LCD_RES: GPIOB.10 with pinCMx 27 on package pin 62 */
#define LCD_LCD_RES_PIN                                         (DL_GPIO_PIN_10)
#define LCD_LCD_RES_IOMUX                                        (IOMUX_PINCM27)
/* Defines for LCD_DC: GPIOB.11 with pinCMx 28 on package pin 63 */
#define LCD_LCD_DC_PIN                                          (DL_GPIO_PIN_11)
#define LCD_LCD_DC_IOMUX                                         (IOMUX_PINCM28)
/* Defines for LCD_CS: GPIOB.14 with pinCMx 31 on package pin 2 */
#define LCD_LCD_CS_PIN                                          (DL_GPIO_PIN_14)
#define LCD_LCD_CS_IOMUX                                         (IOMUX_PINCM31)
/* Defines for LCD_BLK: GPIOB.26 with pinCMx 57 on package pin 28 */
#define LCD_LCD_BLK_PIN                                         (DL_GPIO_PIN_26)
#define LCD_LCD_BLK_IOMUX                                        (IOMUX_PINCM57)
/* Port definition for Pin Group motor */
#define motor_PORT                                                       (GPIOB)

/* Defines for left_1: GPIOB.12 with pinCMx 29 on package pin 64 */
#define motor_left_1_PIN                                        (DL_GPIO_PIN_12)
#define motor_left_1_IOMUX                                       (IOMUX_PINCM29)
/* Defines for left_2: GPIOB.13 with pinCMx 30 on package pin 1 */
#define motor_left_2_PIN                                        (DL_GPIO_PIN_13)
#define motor_left_2_IOMUX                                       (IOMUX_PINCM30)
/* Defines for right_1: GPIOB.2 with pinCMx 15 on package pin 50 */
#define motor_right_1_PIN                                        (DL_GPIO_PIN_2)
#define motor_right_1_IOMUX                                      (IOMUX_PINCM15)
/* Defines for right_2: GPIOB.3 with pinCMx 16 on package pin 51 */
#define motor_right_2_PIN                                        (DL_GPIO_PIN_3)
#define motor_right_2_IOMUX                                      (IOMUX_PINCM16)
/* Port definition for Pin Group MPU6050 */
#define MPU6050_PORT                                                     (GPIOA)

/* Defines for CLK: GPIOA.13 with pinCMx 35 on package pin 6 */
#define MPU6050_CLK_PIN                                         (DL_GPIO_PIN_13)
#define MPU6050_CLK_IOMUX                                        (IOMUX_PINCM35)
/* Defines for SDA: GPIOA.12 with pinCMx 34 on package pin 5 */
#define MPU6050_SDA_PIN                                         (DL_GPIO_PIN_12)
#define MPU6050_SDA_IOMUX                                        (IOMUX_PINCM34)
/* Defines for NVIC_IN: GPIOA.22 with pinCMx 47 on package pin 18 */
// pins affected by this interrupt request:["NVIC_IN"]
#define MPU6050_INT_IRQN                                        (GPIOA_INT_IRQn)
#define MPU6050_INT_IIDX                        (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define MPU6050_NVIC_IN_IIDX                                (DL_GPIO_IIDX_DIO22)
#define MPU6050_NVIC_IN_PIN                                     (DL_GPIO_PIN_22)
#define MPU6050_NVIC_IN_IOMUX                                    (IOMUX_PINCM47)
/* Port definition for Pin Group xun_ji */
#define xun_ji_PORT                                                      (GPIOB)

/* Defines for left_SH: GPIOB.7 with pinCMx 24 on package pin 59 */
#define xun_ji_left_SH_PIN                                       (DL_GPIO_PIN_7)
#define xun_ji_left_SH_IOMUX                                     (IOMUX_PINCM24)
/* Defines for left_CL: GPIOB.4 with pinCMx 17 on package pin 52 */
#define xun_ji_left_CL_PIN                                       (DL_GPIO_PIN_4)
#define xun_ji_left_CL_IOMUX                                     (IOMUX_PINCM17)
/* Defines for left_DA: GPIOB.5 with pinCMx 18 on package pin 53 */
#define xun_ji_left_DA_PIN                                       (DL_GPIO_PIN_5)
#define xun_ji_left_DA_IOMUX                                     (IOMUX_PINCM18)
/* Defines for right_SH: GPIOB.6 with pinCMx 23 on package pin 58 */
#define xun_ji_right_SH_PIN                                      (DL_GPIO_PIN_6)
#define xun_ji_right_SH_IOMUX                                    (IOMUX_PINCM23)
/* Defines for right_CL: GPIOB.23 with pinCMx 51 on package pin 22 */
#define xun_ji_right_CL_PIN                                     (DL_GPIO_PIN_23)
#define xun_ji_right_CL_IOMUX                                    (IOMUX_PINCM51)
/* Defines for right_DA: GPIOB.27 with pinCMx 58 on package pin 29 */
#define xun_ji_right_DA_PIN                                     (DL_GPIO_PIN_27)
#define xun_ji_right_DA_IOMUX                                    (IOMUX_PINCM58)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_right_CAP_A_init(void);
void SYSCFG_DL_right_CAP_B_init(void);
void SYSCFG_DL_left_CAP_A_init(void);
void SYSCFG_DL_left_CAP_B_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_TIMER_1_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_SPI_1_init(void);



bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
