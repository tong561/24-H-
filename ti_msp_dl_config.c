/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerG_backupConfig gPWM_0Backup;
DL_TimerA_backupConfig gleft_CAP_ABackup;
DL_TimerA_backupConfig gleft_CAP_BBackup;
DL_TimerG_backupConfig gTIMER_0Backup;
DL_SPI_backupConfig gSPI_1Backup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_PWM_0_init();
    SYSCFG_DL_right_CAP_A_init();
    SYSCFG_DL_right_CAP_B_init();
    SYSCFG_DL_left_CAP_A_init();
    SYSCFG_DL_left_CAP_B_init();
    SYSCFG_DL_TIMER_0_init();
    SYSCFG_DL_TIMER_1_init();
    SYSCFG_DL_UART_0_init();
    SYSCFG_DL_SPI_1_init();
    /* Ensure backup structures have no valid state */
	gPWM_0Backup.backupRdy 	= false;
	gleft_CAP_ABackup.backupRdy 	= false;
	gleft_CAP_BBackup.backupRdy 	= false;
	gTIMER_0Backup.backupRdy 	= false;

	gSPI_1Backup.backupRdy 	= false;

}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerG_saveConfiguration(PWM_0_INST, &gPWM_0Backup);
	retStatus &= DL_TimerA_saveConfiguration(left_CAP_A_INST, &gleft_CAP_ABackup);
	retStatus &= DL_TimerA_saveConfiguration(left_CAP_B_INST, &gleft_CAP_BBackup);
	retStatus &= DL_TimerG_saveConfiguration(TIMER_0_INST, &gTIMER_0Backup);
	retStatus &= DL_SPI_saveConfiguration(SPI_1_INST, &gSPI_1Backup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerG_restoreConfiguration(PWM_0_INST, &gPWM_0Backup, false);
	retStatus &= DL_TimerA_restoreConfiguration(left_CAP_A_INST, &gleft_CAP_ABackup, false);
	retStatus &= DL_TimerA_restoreConfiguration(left_CAP_B_INST, &gleft_CAP_BBackup, false);
	retStatus &= DL_TimerG_restoreConfiguration(TIMER_0_INST, &gTIMER_0Backup, false);
	retStatus &= DL_SPI_restoreConfiguration(SPI_1_INST, &gSPI_1Backup);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerG_reset(PWM_0_INST);
    DL_TimerG_reset(right_CAP_A_INST);
    DL_TimerG_reset(right_CAP_B_INST);
    DL_TimerA_reset(left_CAP_A_INST);
    DL_TimerA_reset(left_CAP_B_INST);
    DL_TimerG_reset(TIMER_0_INST);
    DL_TimerG_reset(TIMER_1_INST);
    DL_UART_Main_reset(UART_0_INST);
    DL_SPI_reset(SPI_1_INST);
    DL_MathACL_reset(MATHACL);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerG_enablePower(PWM_0_INST);
    DL_TimerG_enablePower(right_CAP_A_INST);
    DL_TimerG_enablePower(right_CAP_B_INST);
    DL_TimerA_enablePower(left_CAP_A_INST);
    DL_TimerA_enablePower(left_CAP_B_INST);
    DL_TimerG_enablePower(TIMER_0_INST);
    DL_TimerG_enablePower(TIMER_1_INST);
    DL_UART_Main_enablePower(UART_0_INST);
    DL_SPI_enablePower(SPI_1_INST);
    DL_MathACL_enablePower(MATHACL);
    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXIN_IOMUX);
    DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXOUT_IOMUX);

    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_0_C0_IOMUX,GPIO_PWM_0_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_0_C0_PORT, GPIO_PWM_0_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_0_C1_IOMUX,GPIO_PWM_0_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_0_C1_PORT, GPIO_PWM_0_C1_PIN);
    
	DL_GPIO_initPeripheralOutputFunction(
		 GPIO_PWM_0_C0_IOMUX, GPIO_PWM_0_C0_IOMUX_FUNC);
	DL_GPIO_initPeripheralOutputFunction(
		 GPIO_PWM_0_C1_IOMUX, GPIO_PWM_0_C1_IOMUX_FUNC);

    
	DL_GPIO_initPeripheralInputFunctionFeatures(
		 GPIO_right_CAP_A_C1_IOMUX, GPIO_right_CAP_A_C1_IOMUX_FUNC,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);
    
	DL_GPIO_initPeripheralInputFunctionFeatures(
		 GPIO_right_CAP_B_C0_IOMUX, GPIO_right_CAP_B_C0_IOMUX_FUNC,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);
    
	DL_GPIO_initPeripheralInputFunctionFeatures(
		 GPIO_left_CAP_A_C0_IOMUX, GPIO_left_CAP_A_C0_IOMUX_FUNC,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);
    
	DL_GPIO_initPeripheralInputFunctionFeatures(
		 GPIO_left_CAP_B_C0_IOMUX, GPIO_left_CAP_B_C0_IOMUX_FUNC,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    
	DL_GPIO_initPeripheralOutputFunction(
		 GPIO_UART_0_IOMUX_TX, GPIO_UART_0_IOMUX_TX_FUNC);
	DL_GPIO_initPeripheralInputFunctionFeatures(
		 GPIO_UART_0_IOMUX_RX, GPIO_UART_0_IOMUX_RX_FUNC,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initPeripheralInputFunction(
        GPIO_SPI_1_IOMUX_POCI, GPIO_SPI_1_IOMUX_POCI_FUNC);
    
	DL_GPIO_initPeripheralOutputFunctionFeatures(
		 GPIO_SPI_1_IOMUX_SCLK, GPIO_SPI_1_IOMUX_SCLK_FUNC,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_DRIVE_STRENGTH_LOW, DL_GPIO_HIZ_DISABLE);
	DL_GPIO_initPeripheralOutputFunctionFeatures(
		 GPIO_SPI_1_IOMUX_PICO, GPIO_SPI_1_IOMUX_PICO_FUNC,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_DRIVE_STRENGTH_LOW, DL_GPIO_HIZ_DISABLE);

    DL_GPIO_initDigitalInputFeatures(Key_Munber_PIN_Key_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(LCD_LCD_RES_IOMUX);

    DL_GPIO_initDigitalOutput(LCD_LCD_DC_IOMUX);

    DL_GPIO_initDigitalOutput(LCD_LCD_CS_IOMUX);

    DL_GPIO_initDigitalOutput(LCD_LCD_BLK_IOMUX);

    DL_GPIO_initDigitalOutput(motor_left_1_IOMUX);

    DL_GPIO_initDigitalOutput(motor_left_2_IOMUX);

    DL_GPIO_initDigitalOutput(motor_right_1_IOMUX);

    DL_GPIO_initDigitalOutput(motor_right_2_IOMUX);

    DL_GPIO_initDigitalOutput(MPU6050_CLK_IOMUX);

    DL_GPIO_initDigitalOutput(MPU6050_SDA_IOMUX);

    DL_GPIO_initDigitalInputFeatures(MPU6050_NVIC_IN_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(xun_ji_left_SH_IOMUX);

    DL_GPIO_initDigitalOutput(xun_ji_left_CL_IOMUX);

    DL_GPIO_initDigitalInputFeatures(xun_ji_left_DA_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(xun_ji_right_SH_IOMUX);

    DL_GPIO_initDigitalOutput(xun_ji_right_CL_IOMUX);

    DL_GPIO_initDigitalInputFeatures(xun_ji_right_DA_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_setPins(GPIOA, MPU6050_CLK_PIN |
		MPU6050_SDA_PIN);
    DL_GPIO_enableOutput(GPIOA, MPU6050_CLK_PIN |
		MPU6050_SDA_PIN);
    DL_GPIO_setUpperPinsPolarity(GPIOA, DL_GPIO_PIN_22_EDGE_FALL);
    DL_GPIO_setUpperPinsInputFilter(GPIOA, DL_GPIO_PIN_16_INPUT_FILTER_8_CYCLES);
    DL_GPIO_clearInterruptStatus(GPIOA, MPU6050_NVIC_IN_PIN);
    DL_GPIO_enableInterrupt(GPIOA, MPU6050_NVIC_IN_PIN);
    DL_GPIO_clearPins(GPIOB, LCD_LCD_RES_PIN |
		LCD_LCD_BLK_PIN |
		xun_ji_left_SH_PIN |
		xun_ji_left_CL_PIN |
		xun_ji_right_SH_PIN |
		xun_ji_right_CL_PIN);
    DL_GPIO_setPins(GPIOB, LCD_LCD_DC_PIN |
		LCD_LCD_CS_PIN |
		motor_left_1_PIN |
		motor_left_2_PIN |
		motor_right_1_PIN |
		motor_right_2_PIN);
    DL_GPIO_enableOutput(GPIOB, LCD_LCD_RES_PIN |
		LCD_LCD_DC_PIN |
		LCD_LCD_CS_PIN |
		LCD_LCD_BLK_PIN |
		motor_left_1_PIN |
		motor_left_2_PIN |
		motor_right_1_PIN |
		motor_right_2_PIN |
		xun_ji_left_SH_PIN |
		xun_ji_left_CL_PIN |
		xun_ji_right_SH_PIN |
		xun_ji_right_CL_PIN);

}


static const DL_SYSCTL_SYSPLLConfig gSYSPLLConfig = {
    .inputFreq              = DL_SYSCTL_SYSPLL_INPUT_FREQ_32_48_MHZ,
	.rDivClk2x              = 1,
	.rDivClk1               = 0,
	.rDivClk0               = 0,
	.enableCLK2x            = DL_SYSCTL_SYSPLL_CLK2X_DISABLE,
	.enableCLK1             = DL_SYSCTL_SYSPLL_CLK1_DISABLE,
	.enableCLK0             = DL_SYSCTL_SYSPLL_CLK0_ENABLE,
	.sysPLLMCLK             = DL_SYSCTL_SYSPLL_MCLK_CLK0,
	.sysPLLRef              = DL_SYSCTL_SYSPLL_REF_SYSOSC,
	.qDiv                   = 4,
	.pDiv                   = DL_SYSCTL_SYSPLL_PDIV_1
};
SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);
    DL_SYSCTL_setFlashWaitState(DL_SYSCTL_FLASH_WAIT_STATE_2);

    
	DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
	/* Set default configuration */
	DL_SYSCTL_disableHFXT();
	DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_setHFCLKSourceHFXTParams(DL_SYSCTL_HFXT_RANGE_32_48_MHZ,0, false);
    DL_SYSCTL_configSYSPLL((DL_SYSCTL_SYSPLLConfig *) &gSYSPLLConfig);
    DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_2);
    DL_SYSCTL_setHFCLKDividerForMFPCLK(DL_SYSCTL_HFCLK_MFPCLK_DIVIDER_10);
    DL_SYSCTL_enableMFCLK();
    DL_SYSCTL_enableMFPCLK();
	DL_SYSCTL_setMFPCLKSource(DL_SYSCTL_MFPCLK_SOURCE_HFCLK);
    DL_SYSCTL_setMCLKSource(SYSOSC, HSCLK, DL_SYSCTL_HSCLK_SOURCE_SYSPLL);
    /* INT_GROUP1 Priority */
    NVIC_SetPriority(GPIOA_INT_IRQn, 1);

}


/*
 * Timer clock configuration to be sourced by  / 4 (20000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   20000000 Hz = 20000000 Hz / (4 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gPWM_0ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_4,
    .prescale = 0U
};

static const DL_TimerG_PWMConfig gPWM_0Config = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 1000,
    .isTimerWithFourCC = false,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_0_init(void) {

    DL_TimerG_setClockConfig(
        PWM_0_INST, (DL_TimerG_ClockConfig *) &gPWM_0ClockConfig);

    DL_TimerG_initPWMMode(
        PWM_0_INST, (DL_TimerG_PWMConfig *) &gPWM_0Config);

    // Set Counter control to the smallest CC index being used
    DL_TimerG_setCounterControl(PWM_0_INST,DL_TIMER_CZC_CCCTL0_ZCOND,DL_TIMER_CAC_CCCTL0_ACOND,DL_TIMER_CLC_CCCTL0_LCOND);

    DL_TimerG_setCaptureCompareOutCtl(PWM_0_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_ENABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_0_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_0_INST, 1000, DL_TIMER_CC_0_INDEX);

    DL_TimerG_setCaptureCompareOutCtl(PWM_0_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_ENABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_0_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_0_INST, 1000, DL_TIMER_CC_1_INDEX);

    DL_TimerG_enableClock(PWM_0_INST);


    
    DL_TimerG_setCCPDirection(PWM_0_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );


}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (40000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   40000000 Hz = 40000000 Hz / (2 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gright_CAP_AClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_2,
    .prescale = 0U
};

static const DL_TimerG_CompareConfig gright_CAP_ACompareConfig = {
    .compareMode    = DL_TIMER_COMPARE_MODE_EDGE_COUNT_UP,
    .count          = 59999,
    .startTimer     = DL_TIMER_START,
    .edgeDetectMode = DL_TIMER_COMPARE_EDGE_DETECTION_MODE_EDGE,
    .inputChan      = DL_TIMER_INPUT_CHAN_1,
    .inputInvMode   = DL_TIMER_CC_INPUT_INV_NOINVERT,
};

SYSCONFIG_WEAK void SYSCFG_DL_right_CAP_A_init(void) {

    DL_TimerG_setClockConfig(right_CAP_A_INST,
        (DL_TimerG_ClockConfig *) &gright_CAP_AClockConfig);
    DL_TimerG_initCompareMode(right_CAP_A_INST,
        (DL_TimerG_CompareConfig *) &gright_CAP_ACompareConfig);
    DL_TimerG_setCaptureCompareInputFilter(right_CAP_A_INST,
        DL_TIMER_CC_INPUT_FILT_CPV_CONSEC_PER, DL_TIMER_CC_INPUT_FILT_FP_PER_8,
        DL_TIMER_CC_1_INDEX);
    DL_TimerG_enableCaptureCompareInputFilter(right_CAP_A_INST,
        DL_TIMER_CC_1_INDEX);

    DL_TimerG_enableClock(right_CAP_A_INST);




}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (20000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   20000000 Hz = 20000000 Hz / (2 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gright_CAP_BClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_2,
    .prescale = 0U
};

static const DL_TimerG_CompareConfig gright_CAP_BCompareConfig = {
    .compareMode    = DL_TIMER_COMPARE_MODE_EDGE_COUNT_UP,
    .count          = 59999,
    .startTimer     = DL_TIMER_START,
    .edgeDetectMode = DL_TIMER_COMPARE_EDGE_DETECTION_MODE_EDGE,
    .inputChan      = DL_TIMER_INPUT_CHAN_0,
    .inputInvMode   = DL_TIMER_CC_INPUT_INV_NOINVERT,
};

SYSCONFIG_WEAK void SYSCFG_DL_right_CAP_B_init(void) {

    DL_TimerG_setClockConfig(right_CAP_B_INST,
        (DL_TimerG_ClockConfig *) &gright_CAP_BClockConfig);
    DL_TimerG_initCompareMode(right_CAP_B_INST,
        (DL_TimerG_CompareConfig *) &gright_CAP_BCompareConfig);
    DL_TimerG_setCaptureCompareInputFilter(right_CAP_B_INST,
        DL_TIMER_CC_INPUT_FILT_CPV_CONSEC_PER, DL_TIMER_CC_INPUT_FILT_FP_PER_8,
        DL_TIMER_CC_0_INDEX);
    DL_TimerG_enableCaptureCompareInputFilter(right_CAP_B_INST,
        DL_TIMER_CC_0_INDEX);

    DL_TimerG_enableClock(right_CAP_B_INST);




}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (40000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   40000000 Hz = 40000000 Hz / (2 * (0 + 1))
 */
static const DL_TimerA_ClockConfig gleft_CAP_AClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_2,
    .prescale = 0U
};

static const DL_TimerA_CompareConfig gleft_CAP_ACompareConfig = {
    .compareMode    = DL_TIMER_COMPARE_MODE_EDGE_COUNT_UP,
    .count          = 59999,
    .startTimer     = DL_TIMER_START,
    .edgeDetectMode = DL_TIMER_COMPARE_EDGE_DETECTION_MODE_EDGE,
    .inputChan      = DL_TIMER_INPUT_CHAN_0,
    .inputInvMode   = DL_TIMER_CC_INPUT_INV_NOINVERT,
};

SYSCONFIG_WEAK void SYSCFG_DL_left_CAP_A_init(void) {

    DL_TimerA_setClockConfig(left_CAP_A_INST,
        (DL_TimerA_ClockConfig *) &gleft_CAP_AClockConfig);
    DL_TimerA_initCompareMode(left_CAP_A_INST,
        (DL_TimerA_CompareConfig *) &gleft_CAP_ACompareConfig);
    DL_TimerA_setCaptureCompareInputFilter(left_CAP_A_INST,
        DL_TIMER_CC_INPUT_FILT_CPV_CONSEC_PER, DL_TIMER_CC_INPUT_FILT_FP_PER_8,
        DL_TIMER_CC_0_INDEX);
    DL_TimerA_enableCaptureCompareInputFilter(left_CAP_A_INST,
        DL_TIMER_CC_0_INDEX);

    DL_TimerA_enableClock(left_CAP_A_INST);




}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (40000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   40000000 Hz = 40000000 Hz / (2 * (0 + 1))
 */
static const DL_TimerA_ClockConfig gleft_CAP_BClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_2,
    .prescale = 0U
};

static const DL_TimerA_CompareConfig gleft_CAP_BCompareConfig = {
    .compareMode    = DL_TIMER_COMPARE_MODE_EDGE_COUNT_UP,
    .count          = 59999,
    .startTimer     = DL_TIMER_START,
    .edgeDetectMode = DL_TIMER_COMPARE_EDGE_DETECTION_MODE_EDGE,
    .inputChan      = DL_TIMER_INPUT_CHAN_0,
    .inputInvMode   = DL_TIMER_CC_INPUT_INV_NOINVERT,
};

SYSCONFIG_WEAK void SYSCFG_DL_left_CAP_B_init(void) {

    DL_TimerA_setClockConfig(left_CAP_B_INST,
        (DL_TimerA_ClockConfig *) &gleft_CAP_BClockConfig);
    DL_TimerA_initCompareMode(left_CAP_B_INST,
        (DL_TimerA_CompareConfig *) &gleft_CAP_BCompareConfig);
    DL_TimerA_setCaptureCompareInputFilter(left_CAP_B_INST,
        DL_TIMER_CC_INPUT_FILT_CPV_CONSEC_PER, DL_TIMER_CC_INPUT_FILT_FP_PER_8,
        DL_TIMER_CC_0_INDEX);
    DL_TimerA_enableCaptureCompareInputFilter(left_CAP_B_INST,
        DL_TIMER_CC_0_INDEX);

    DL_TimerA_enableClock(left_CAP_B_INST);




}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (10000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   1000000 Hz = 10000000 Hz / (8 * (9 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_0ClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 9U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_0_INST_LOAD_VALUE = (2.5 ms * 1000000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_0TimerConfig = {
    .period     = TIMER_0_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_0_init(void) {

    DL_TimerG_setClockConfig(TIMER_0_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_0ClockConfig);

    DL_TimerG_initTimerMode(TIMER_0_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_0TimerConfig);
    DL_TimerG_enableInterrupt(TIMER_0_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
	NVIC_SetPriority(TIMER_0_INST_INT_IRQN, 0);
    DL_TimerG_enableClock(TIMER_0_INST);





}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (5000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   5000000 Hz = 5000000 Hz / (8 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_1ClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 0U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_1_INST_LOAD_VALUE = (5 ms * 5000000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_1TimerConfig = {
    .period     = TIMER_1_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_1_init(void) {

    DL_TimerG_setClockConfig(TIMER_1_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_1ClockConfig);

    DL_TimerG_initTimerMode(TIMER_1_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_1TimerConfig);
    DL_TimerG_enableInterrupt(TIMER_1_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
	NVIC_SetPriority(TIMER_1_INST_INT_IRQN, 1);
    DL_TimerG_enableClock(TIMER_1_INST);





}



static const DL_UART_Main_ClockConfig gUART_0ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_0Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_0_init(void)
{
    DL_UART_Main_setClockConfig(UART_0_INST, (DL_UART_Main_ClockConfig *) &gUART_0ClockConfig);

    DL_UART_Main_init(UART_0_INST, (DL_UART_Main_Config *) &gUART_0Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115190.78
     */
    DL_UART_Main_setOversampling(UART_0_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_0_INST, UART_0_IBRD_40_MHZ_115200_BAUD, UART_0_FBRD_40_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_0_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);
    /* Setting the Interrupt Priority */
    NVIC_SetPriority(UART_0_INST_INT_IRQN, 1);


    DL_UART_Main_enable(UART_0_INST);
}

static const DL_SPI_Config gSPI_1_config = {
    .mode        = DL_SPI_MODE_CONTROLLER,
    .frameFormat = DL_SPI_FRAME_FORMAT_MOTO3_POL0_PHA0,
    .parity      = DL_SPI_PARITY_NONE,
    .dataSize    = DL_SPI_DATA_SIZE_8,
    .bitOrder    = DL_SPI_BIT_ORDER_MSB_FIRST,
};

static const DL_SPI_ClockConfig gSPI_1_clockConfig = {
    .clockSel    = DL_SPI_CLOCK_BUSCLK,
    .divideRatio = DL_SPI_CLOCK_DIVIDE_RATIO_1
};

SYSCONFIG_WEAK void SYSCFG_DL_SPI_1_init(void) {
    DL_SPI_setClockConfig(SPI_1_INST, (DL_SPI_ClockConfig *) &gSPI_1_clockConfig);

    DL_SPI_init(SPI_1_INST, (DL_SPI_Config *) &gSPI_1_config);

    /* Configure Controller mode */
    /*
     * Set the bit rate clock divider to generate the serial output clock
     *     outputBitRate = (spiInputClock) / ((1 + SCR) * 2)
     *     8000000 = (80000000)/((1 + 4) * 2)
     */
    DL_SPI_setBitRateSerialClockDivider(SPI_1_INST, 4);
    /* Set RX and TX FIFO threshold levels */
    DL_SPI_setFIFOThreshold(SPI_1_INST, DL_SPI_RX_FIFO_LEVEL_1_2_FULL, DL_SPI_TX_FIFO_LEVEL_1_2_EMPTY);

    /* Enable module */
    DL_SPI_enable(SPI_1_INST);
}

