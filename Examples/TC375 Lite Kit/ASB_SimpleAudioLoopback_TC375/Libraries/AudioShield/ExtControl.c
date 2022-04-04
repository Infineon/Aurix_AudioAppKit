/******************************************************************************
 * ExtControl.c
 * Copyright (C) Infineon Technologies AG 2021
 *
 * Use of this file is subject to the terms of use agreed between (i) you or
 * the company in which ordinary course of business you are acting and (ii)
 * Infineon Technologies AG or its licensees. If and as long as no such terms
 * of use are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated
 * by a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *****************************************************************************/


/*****************************************************************************/
/*----------------------------------Includes---------------------------------*/
/*****************************************************************************/

#include <AudioShield/Audio.h>
#include "Ifx_reg.h"
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include <math.h>

/*****************************************************************************/
/*-----------------------------------Macros----------------------------------*/
/*****************************************************************************/

/*****************************************************************************/
/*------------------------------Global variables-----------------------------*/
/*****************************************************************************/

uint8_t SwitchState[2];
uint8_t AmpIsMute = 1;

/*****************************************************************************/
/*-------------------------------Data Structures-----------------------------*/
/*****************************************************************************/

/*****************************************************************************/
/*-------------------------Private Variables/Constants-----------------------*/
/*****************************************************************************/

/*****************************************************************************/
/*----------------------------Function Prototypes----------------------------*/
/*****************************************************************************/

/*****************************************************************************/
/*-------------------------Function Implementations--------------------------*/
/*****************************************************************************/




/*
 * This functions initializes AN0 input connected to the poti on TC375LK (next to USB input plug) but also the user-button and LED1 to control the muting of MA12070P amp
 */
void InitButtonADC(void){


       //Init LED1 (P00.5) as output and set to high (led off) as the led-circuit is active-low
       P00_IOCR4.B.PC5 = 0x10;
       P00_OUT.B.P5 = 1;


       //Enable ADC clock
       IfxScuWdt_clearCpuEndinit(IfxScuWdt_getCpuWatchdogPassword ()); //enable access to the clock system
       EVADC_CLC.U = 0; //enable the ADC clock
       IfxScuWdt_setCpuEndinit (IfxScuWdt_getCpuWatchdogPassword ()); //lock the clock system access again



       //Init ADC for pin AN0 (ADC-Group 0, Channel 0)

       EVADC_G0_ANCFG.B.DIVA = 0x1f; //set analog clock divider to slowest
       EVADC_G0ARBCFG.B.ANONC = 3; //normal operation, conversion starts immediately

       //Do Calibration
       EVADC_GLOBCFG.B.SUCAL = 1;  //start calibration
       while(EVADC_G0_ARBCFG.B.CAL == 1); //wait until calibration has finished


       EVADC_G0ARBPR.B.ASEN0 = 1; //enable arbitration
       EVADC_G0ARBPR.B.PRIO0 = 0; //standard priority
       EVADC_G0ARBPR.B.CSM0 = 1; //conversions can cancel other sources

       EVADC_G0QMR0.B.ENGT = 1; //enable conversions in the queue
       EVADC_G0ICLASS0.B.STCS = 2; //sample time = ADCI/4

       EVADC_G0QCTRL0.U |=  (0x1 << 15) | (0x0 << 6);
       EVADC_G0QINR0.U = (1 << 5) | 0; //automatic refill the queue -> constant ADC updating

       EVADC_G0_CHCTR0.B.RESREG = 0; //store result in res-register 0

       //from now on, ADC is constantly running (without further triggering)

}

/*
 * This functions reads the absolute value from the poti/ADC (0..4095),
 * remaps this value range into a logarithmic dB scale from -70dB to +10dB and
 * finally converts the logarithmic dB-scaled value into a linear multiplication factor (return value)
 */

float ReadADCVolume(void) {

    //get latest ADC result from result-register 0
    float ADC_Result = (float) EVADC_G0RES0.B.RESULT;

    //map adc-value from 0 to 4096 to -70 to +20 (dB log scale) -> see Arduino map() function as reference
    float in_min = 0.0f;
    float in_max = 4095.0f;
    float out_min = -70.0f;
    float out_max = 10.0f;
    float volume_dB_level = (ADC_Result-in_min) * (out_max-out_min)/(in_max-in_min)+out_min;

    //calculate from dB scale into linear multiplication factor
    float volume_linear_level = powf(10.0f,(volume_dB_level/20.0f));

    return volume_linear_level;
}

/*
 * loads the actual user-button-level (P00.7) into a shift register
 * as soon as a falling edge (button pressed) is detected, the amp will get muted/unmuted and signaled by LED1
 */
void CheckAmpMute(void) {

    //load button-level into two-tab shift-register
    SwitchState[1] = SwitchState[0];
    SwitchState[0] = P00_IN.B.P7;

    //check if switch has toggled
    if (SwitchState[1]==1 && SwitchState[0]==0) {

        //if amp was muted before, unmute amp and turn on LED1 (P00.5)
        if (AmpIsMute==1) {
            AmpIsMute=0;
            UnmuteAmp();
            P00_OUT.B.P5 = 0;
        }
        else {
            AmpIsMute=1;
            MuteAmp();
            P00_OUT.B.P5 = 1;
        }
    }
}

/*
 * this is being used at startup to check if button was pressed at startup to activate / deactivate volume control via poti
 */
uint8_t UserButtonPressedStartup(void) {
    return P00_IN.B.P7;
}
