/******************************************************************************
 * AudioTask.c
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

#include <stdint.h>
#include <math.h>
#include "Audio.h"
#include "LedArray.h"
#include "ExtControl.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include <Ifx_reg.h>
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

/*****************************************************************************/
/*-----------------------------------Macros----------------------------------*/
/*****************************************************************************/

/*****************************************************************************/
/*------------------------------Global variables-----------------------------*/
/*****************************************************************************/

TaskHandle_t AudioProcess_task_handler = NULL;

//Audio RX/TX Buffer
extern int32_t __attribute__ ((__align(4*1024))) rxBuf[4096];
extern int32_t __attribute__ ((__align(4*1024))) txBuf[4096];

//Volume
float volume=1.0f;

//decide here if the poti/adc should be used for volume-control
uint8_t useADCVolumeControl = 0;

//variable for microphone selection via user-button
uint8_t LEDActiveChannel=0;

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






int32_t SampleSaturate (float inSample) {

    /*
     * Max sample value can be +/- 2^31. So before back-conversion from float to int_32 we need to saturate the sample (otherwise distorted sound might appear)
     */

    if (inSample > 2147400000.0f) inSample = 2147400000.0f;
    if (inSample < -2147400000.0f) inSample = -2147400000.0f;
    return (int32_t) roundf(inSample);
}


/*
 * Interrupt from RX-DMA at every buffer-switchover (as of current configuration every 64 samples (or 32 stereo-samples)
 */
IFX_INTERRUPT (DMA_INTERRUPT, 0, 30)
{

    //Clear DMA Frozen Bit for I²S RX/TX DMA
    DMA_CHCSR050.B.FROZEN = 0;
    DMA_CHCSR049.B.FROZEN = 0;

    //Unblock Audio Process Task and force context switch
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR( AudioProcess_task_handler, &xHigherPriorityTaskWoken );
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

}


static __attribute__((__noreturn__)) void OsTask_AudioProcess(void *arg)
{
    (void)arg;



    //Set Audio-Source to input from A²B (->1)
    //if set to 0, the Line-In input from Audio-Codec is selected
    Set_TDM_DataIn_Mux(1);

    //start I2S emulation; critical section should not be interrupted by context switch
    taskENTER_CRITICAL();
    TDM8_Init_DMA();
    taskEXIT_CRITICAL();


    //Init A²B Network and Audio Codec
    Init_A2B_Codec();


    float TDM_IN[8];
    float lSample, rSample;
    uint8_t ActiveBuffer;



    //variable for level-meter
    int  LevelBlockCount = 20;
    float LevelMaxTemp;
    int8_t LevelBlockCounter=0;


    while (1)
    {
        //wait for task unblock from ISR
        ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

        //check DMA which buffer we should operate on
        if (DMA_CHCSR050.B.BUFFER == 0) ActiveBuffer = 1;
        else ActiveBuffer = 0;

        //calculate buffer offset dependent if DMA currently operates on first or second buffer half
        int BufferOffset = ActiveBuffer ? 2048 : 0;

        for (int i=0+BufferOffset; i<2048+BufferOffset; i=i+8) {
            TDM_IN[0] = (float) rxBuf[i+0];
            TDM_IN[1] = (float) rxBuf[i+1];
            TDM_IN[2] = (float) rxBuf[i+2];
            TDM_IN[3] = (float) rxBuf[i+3];
            TDM_IN[4] = (float) rxBuf[i+4];
            TDM_IN[5] = (float) rxBuf[i+5];
            TDM_IN[6] = (float) rxBuf[i+6];
            TDM_IN[7] = (float) rxBuf[i+7];

            //Get maximum level for LED array
            if (fabs( TDM_IN[LEDActiveChannel]) > LevelMaxTemp) {
                        LevelMaxTemp = fabs(TDM_IN[LEDActiveChannel]);
            }


            lSample = (TDM_IN[0] + TDM_IN[2] + TDM_IN[4] + TDM_IN[6])*volume;
            rSample = (TDM_IN[1] + TDM_IN[3] + TDM_IN[5] + TDM_IN[7])*volume;

            //Stereo Audio-DAC is on Slot 0+4;
            txBuf[i] = (int32_t) SampleSaturate(lSample);
            txBuf[i+4] = (int32_t) SampleSaturate(rSample);
        }


        //show level on led array
        if (LevelBlockCounter<LevelBlockCount) {
            LevelBlockCounter++;
        }
        else {
            LevelBlockCounter=0;
            SetLedLevel(LevelMaxTemp);
            LevelMaxTemp = 0.0f;
        }
    }
}



static __attribute__((__noreturn__)) void OsTask_ExternalAudioControl(void *arg)
{

    (void)arg;

    //Init LED Array
    InitLed();

    //Inits ADC for onboard poti and button
    InitButtonADC();

    //Check if user-button pressed at startup -> if yes activate volume control over poti
    if (UserButtonPressedStartup() == 0) {
        useADCVolumeControl = 1;
    }
    else {
        useADCVolumeControl = 0;
        volume = 1.0f;
    }


    while (1) {

        //check if switch has toggled
        if (CheckButtonRuntime()==1) {
            //if yes, count one channel up
            LEDActiveChannel++;
            if (LEDActiveChannel==8) LEDActiveChannel=0;
            ActivateInfoLed(LEDActiveChannel);
        }

        //read volume from poti
        if (useADCVolumeControl==1) {
            volume = ReadADCVolume();
        }

        //Delay 100ms
        vTaskDelay(pdMS_TO_TICKS(100));
    }

}

void AudioTasksCreate(void) {

    //Create Tasks
    xTaskCreate(OsTask_AudioProcess, "Audio task", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 1, &AudioProcess_task_handler);
    xTaskCreate(OsTask_ExternalAudioControl, "Ext. Control task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
}
