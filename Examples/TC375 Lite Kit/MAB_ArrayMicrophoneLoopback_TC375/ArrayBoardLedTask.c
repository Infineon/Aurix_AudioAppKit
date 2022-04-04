/******************************************************************************
 * ArrayBoardLedTask.c
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

#include "ArrayBoardLedTask.h"
#include "Ifx_reg.h"
#include "stdint.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

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
 * Initializes the GPIOs for the LEDs on the microphone array shield
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
 * Activates the 3 Info-LEDs on the microphone-array-shield. The input will be presented binary counted on the LEDs
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
 * Activates a dedicated LED on the LED-circle of the microphone array shield
 */

void ActivateCircleLed(uint8_t ledno) {

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

    if (ledno==0) LED0=1;
    if (ledno==1) LED1=1;
    if (ledno==2) LED2=1;
    if (ledno==3) LED3=1;
    if (ledno==4) LED4=1;
    if (ledno==5) LED5=1;
    if (ledno==6) LED6=1;
    if (ledno==7) LED7=1;
    if (ledno==8) LED8=1;
    if (ledno==9) LED9=1;
    if (ledno==10) LED10=1;
    if (ledno==11) LED11=1;

}

/*
 * Main Task Handler to switch the LEDs on the Array Board
 */

static __attribute__((__noreturn__)) void OsTask_ArrayBoardSwitchLEDs(void *arg)
{

    (void)arg;

    InitLed();

    uint8_t LedInfoActive = 0;
    uint8_t LedCircleActive = 0;

    while (1) {
        ActivateInfoLed(LedInfoActive);
        ActivateCircleLed(LedCircleActive);

        LedInfoActive++;
        LedCircleActive++;

        if (LedInfoActive==8) LedInfoActive=0;
        if (LedCircleActive==12) LedCircleActive=0;

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}


/*
 * Init the LED Task...
 */

void InitArrayBoardLedTask(void) {
    xTaskCreate(OsTask_ArrayBoardSwitchLEDs, "LED Array task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
}
