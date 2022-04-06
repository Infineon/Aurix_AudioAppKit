/******************************************************************************
 * LedArray.c
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

#include <LEDArray.h>
#include "Ifx_reg.h"
#include "stdint.h"

/*****************************************************************************/
/*-----------------------------------Macros----------------------------------*/
/*****************************************************************************/

/*****************************************************************************/
/*------------------------------Global variables-----------------------------*/
/*****************************************************************************/

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
 * This function init's the IO ports of the LEDs on the bottom-shield
 */

void InitLed(void) {
    //led0
    P33_IOCR8.B.PC11 = 0x10;
    //led1
    P33_IOCR12.B.PC12 = 0x10;
    //led2
    P33_IOCR12.B.PC13 = 0x10;
    //led3
    P23_IOCR0.B.PC1 = 0x10;
    //led4
    P23_IOCR0.B.PC0 = 0x10;
    //led5
    P23_IOCR0.B.PC3 = 0x10;
    //led6
    P23_IOCR0.B.PC2 = 0x10;
    //led7
    P22_IOCR0.B.PC1 = 0x10;
    //led8
    P22_IOCR0.B.PC0 = 0x10;
    //led9
    P21_IOCR0.B.PC0 = 0x10;
    //led10
    P22_IOCR0.B.PC2 = 0x10;
    //led11
    P21_IOCR4.B.PC4 = 0x10;

    //ledinfo0
    P21_IOCR4.B.PC5 = 0x10;
    //ledinfo1
    P20_IOCR0.B.PC1 = 0x10;
    //ledinfo2
    P15_IOCR4.B.PC5 = 0x10;

}


/*
 * Activate one if the Info LED for showing which channel is currently selected
 */

void ActivateInfoLed(uint8_t ledno) {
    LEDINFO0 = 0;
    LEDINFO1 = 0;
    LEDINFO2 = 0;
    if (ledno==1) {
        LEDINFO0=1;
    }
    if (ledno==2) {
        LEDINFO1=1;
    }
    if (ledno==3) {
        LEDINFO0=1;
        LEDINFO1=1;
    }
    if (ledno==4) {
        LEDINFO2=1;
    }
    if (ledno==5) {
        LEDINFO0=1;
        LEDINFO2=1;
    }
    if (ledno==6) {
        LEDINFO1=1;
        LEDINFO2=1;
    }
    if (ledno==7) {
        LEDINFO0=1;
        LEDINFO1=1;
        LEDINFO2=1;
    }
}


/*
 * Showing the Audio-Levels on the LEDs
 */
void SetLedLevel(float level) {


    if (level>LEVEL_1dB) {
        LED0 =  1;
        LED1 =  1;
        LED2 =  1;
        LED3 =  1;
        LED4 =  1;
        LED5 =  1;
        LED6 =  1;
        LED7 =  1;
        LED8 =  1;
        LED9 =  1;
        LED10 = 1;
        LED11 = 1;
    }
    else if (level>LEVEL_3dB) {
        LED0 =  0;
        LED1 =  1;
        LED2 =  1;
        LED3 =  1;
        LED4 =  1;
        LED5 =  1;
        LED6 =  1;
        LED7 =  1;
        LED8 =  1;
        LED9 =  1;
        LED10 = 1;
        LED11 = 1;
    }
    else if (level>LEVEL_6dB) {
        LED0 =  0;
        LED1 =  0;
        LED2 =  1;
        LED3 =  1;
        LED4 =  1;
        LED5 =  1;
        LED6 =  1;
        LED7 =  1;
        LED8 =  1;
        LED9 =  1;
        LED10 = 1;
        LED11 = 1;
    }
    else if (level>LEVEL_9dB) {
        LED0 =  0;
        LED1 =  0;
        LED2 =  0;
        LED3 =  1;
        LED4 =  1;
        LED5 =  1;
        LED6 =  1;
        LED7 =  1;
        LED8 =  1;
        LED9 =  1;
        LED10 = 1;
        LED11 = 1;
    }
    else if (level>LEVEL_12dB) {
        LED0 =  0;
        LED1 =  0;
        LED2 =  0;
        LED3 =  0;
        LED4 =  1;
        LED5 =  1;
        LED6 =  1;
        LED7 =  1;
        LED8 =  1;
        LED9 =  1;
        LED10 = 1;
        LED11 = 1;
    }
    else if (level>LEVEL_15dB) {
        LED0 =  0;
        LED1 =  0;
        LED2 =  0;
        LED3 =  0;
        LED4 =  0;
        LED5 =  1;
        LED6 =  1;
        LED7 =  1;
        LED8 =  1;
        LED9 =  1;
        LED10 = 1;
        LED11 = 1;
    }
    else if (level>LEVEL_18dB) {
        LED0 =  0;
        LED1 =  0;
        LED2 =  0;
        LED3 =  0;
        LED4 =  0;
        LED5 =  0;
        LED6 =  1;
        LED7 =  1;
        LED8 =  1;
        LED9 =  1;
        LED10 = 1;
        LED11 = 1;
    }
    else if (level>LEVEL_21dB) {
        LED0 =  0;
        LED1 =  0;
        LED2 =  0;
        LED3 =  0;
        LED4 =  0;
        LED5 =  0;
        LED6 =  0;
        LED7 =  1;
        LED8 =  1;
        LED9 =  1;
        LED10 = 1;
        LED11 = 1;
    }
    else if (level>LEVEL_24dB) {
        LED0 =  0;
        LED1 =  0;
        LED2 =  0;
        LED3 =  0;
        LED4 =  0;
        LED5 =  0;
        LED6 =  0;
        LED7 =  0;
        LED8 =  1;
        LED9 =  1;
        LED10 = 1;
        LED11 = 1;
    }
    else if (level>LEVEL_27dB) {
        LED0 =  0;
        LED1 =  0;
        LED2 =  0;
        LED3 =  0;
        LED4 =  0;
        LED5 =  0;
        LED6 =  0;
        LED7 =  0;
        LED8 =  0;
        LED9 =  1;
        LED10 = 1;
        LED11 = 1;
    }
    else if (level>LEVEL_30dB) {
        LED0 =  0;
        LED1 =  0;
        LED2 =  0;
        LED3 =  0;
        LED4 =  0;
        LED5 =  0;
        LED6 =  0;
        LED7 =  0;
        LED8 =  0;
        LED9 =  0;
        LED10 = 1;
        LED11 = 1;
    }
    else if (level>LEVEL_33dB) {
        LED0 =  0;
        LED1 =  0;
        LED2 =  0;
        LED3 =  0;
        LED4 =  0;
        LED5 =  0;
        LED6 =  0;
        LED7 =  0;
        LED8 =  0;
        LED9 =  0;
        LED10 = 0;
        LED11 = 1;
    }
    else {
        LED0 =  0;
        LED1 =  0;
        LED2 =  0;
        LED3 =  0;
        LED4 =  0;
        LED5 =  0;
        LED6 =  0;
        LED7 =  0;
        LED8 =  0;
        LED9 =  0;
        LED10 = 0;
        LED11 = 0;
    }

}
