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
#include "ExtControl.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include <Ifx_reg.h>
#include "Ifx_Types.h"
/*****************************************************************************/
/*-----------------------------------Macros----------------------------------*/
/*****************************************************************************/

/*****************************************************************************/
/*------------------------------Global variables-----------------------------*/
/*****************************************************************************/

TaskHandle_t AudioProcess_task_handler = NULL;


//Audio RX/TX Buffer
extern int32_t __attribute__ ((__align(4*128))) rxBuf[128];
extern int32_t __attribute__ ((__align(4*128))) txBuf[128];
extern int16_t __attribute__ ((__align(4*2*64))) MicBuf[4][64];
float volume=0.0f;


//decide here if the poti/adc should be used for volume-control
uint8_t useADCVolumeControl = 0;


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
    DMA_CHCSR048.B.FROZEN = 0;
    DMA_CHCSR047.B.FROZEN = 0;
    DMA_CHCSR046.B.FROZEN = 0;
    DMA_CHCSR045.B.FROZEN = 0;

    //Unblock Audio Process Task and force context switch
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR( AudioProcess_task_handler, &xHigherPriorityTaskWoken );
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

}


static __attribute__((__noreturn__)) void OsTask_AudioProcess(void *arg)
{
    (void)arg;


    //Inits I2C
    I2CInit();

    //Use oscillator for fixed 48 kHz sample-rate
    InitRefClockMux(0);

    //start I2S emulation; critical section should not be interrupted by context switch
    taskENTER_CRITICAL();
    I2S_Init_DMA();
    taskEXIT_CRITICAL();

    //init Amp and Codec
    InitAmpAndCodec();



    uint8_t ActiveBuffer;


    while (1)
    {
        //wait for task unblock from ISR
        ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

        //check DMA which buffer we should operate on
        if (DMA_CHCSR050.B.BUFFER == 0) ActiveBuffer = 1;
        else ActiveBuffer = 0;


        float lSample, rSample;

        //calculate buffer offset dependent if DMA currently operates on first or second buffer half
        int MicOffset = ActiveBuffer ? 32 : 0;
        int BufferOffset = ActiveBuffer ? 64 : 0;

        for (int i=0+BufferOffset; i<64+BufferOffset; i=i+2) {

            //sum up the 4 mic channels to a stereo signal
            lSample = ((float) ( (MicBuf[0][MicOffset]<<16) + (MicBuf[1][MicOffset]<<16) ))/2.0f;
            rSample = ((float) ( (MicBuf[2][MicOffset]<<16) + (MicBuf[3][MicOffset]<<16) ))/2.0f;
            MicOffset++;

            //do something with the samples, e.g. manipulate volume
            lSample *= volume;
            rSample *= volume;

            //write back into i2s tx buffer
            txBuf[i] = (int32_t) SampleSaturate(lSample);
            txBuf[i+1] = (int32_t) SampleSaturate(rSample);
        }

    }
}


static __attribute__((__noreturn__)) void OsTask_ExternalAudioControl(void *arg)
{

    (void)arg;

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

        //check if users wants to mute/unmute amplifier
        CheckAmpMute();

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
