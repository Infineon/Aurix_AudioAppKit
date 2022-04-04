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
#include "OpenPDMFilter.h"
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

//PDM Buffers
uint16_t t1, t2;
uint16_t rxBufSplit[2][64];
int16_t MICPCMBuffer[2][16];


//Volume
float volume=1.0f;

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



//PDM Filter struct
TPDMFilter_InitStruct filter0;


int16_t SampleSaturate (float inSample) {

    /*
     * Max sample value can be +/- 2^15. So before back-conversion from float to int_16 we need to saturate the sample (otherwise distorted sound might appear)
     */

    if (inSample > 32700.0f) inSample = 32700.0f;
    if (inSample < -32700.0f) inSample = -32700.0f;
    return (int16_t) roundf(inSample);
}


IFX_INLINE void bmerge (uint16_t in_odd, uint16_t in_even, uint32_t * out_data) {

    /*
     * This function is used to double up the PCM bits as the QSPI is running at double-speed.
     * Please check the user's manual for more information.
     */

    uint32_t merged_value;

    __asm(
            "bmerge %0, %1, %2 \n\t"
            : "=d" (merged_value)
            : "d" (in_odd), "d" (in_even)
          );

    *out_data = merged_value;
}


IFX_INLINE void bsplit(uint32_t indata, uint16_t * out_even, uint16_t * out_odd) {

    /*
     * This function is used to extract the interleaved PDM-data stream into to different buffers
     * Please check the user's manual for more information.
     */
    __asm( "bsplit e14, %0 \n\t"
            "st.h [%1],d14\n\t"
            "st.h [%2],d15\n\t"
            :
            : "d" (indata), "a" (out_even), "a" (out_odd) : "e14"
          );

}

uint16_t bswap16 (uint16_t in) {

    /*
     * Swaps the hi- and low byte
     */

    uint16_t res =
            ((in & 0x00FF)<<8) |
            ((in & 0xFF00)>>8);
    return res;
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

    //Inits I2C
    I2CInit();

    //Use oscillator for fixed 48 kHz sample-rate
    InitRefClockMux(0);


    //Init PDM Filter
    filter0.Fs = 48000;
    filter0.LP_HZ = 20000;
    filter0.HP_HZ = 10;
    filter0.In_MicChannels = 1;     //warning: library was modified to stereo-pdm operation
    filter0.Out_MicChannels = 1;    //warning: library was modified to stereo-pdm operation
    filter0.Decimation = 64;
    filter0.MaxVolume = 64;
    Open_PDM_Filter_Init(&filter0);

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

        //calculate buffer offset dependent if DMA currently operates on first or second buffer half
        int BufferOffset = ActiveBuffer ? 64 : 0;


        //Get PDM Data from input-buffer, split them and apply the bit-swap
        int j = 0;
        for (int i=0+BufferOffset; i<64+BufferOffset; i++) {
            bsplit(rxBuf[i],&t1, &t2);
            rxBufSplit[0][j] = bswap16(t1);
            rxBufSplit[1][j] = bswap16(t2);
            j++;
        }

        //Filter the PDM data to PCM
        Open_PDM_Filter_64(&rxBufSplit[0], &rxBufSplit[1], &MICPCMBuffer[0], &MICPCMBuffer[1], 50, &filter0);


        //Apply volume-modification
        for (int i=0; i<16; i++) {
            MICPCMBuffer[0][i] = SampleSaturate( ((float) MICPCMBuffer[0][i])*volume );
            MICPCMBuffer[1][i] = SampleSaturate( ((float) MICPCMBuffer[1][i])*volume );
        }

        //Double up the PCM bits as I²S interface data-output runs effectively at double-speed and write to I²S TX-Buffer
        uint32_t out_data;
        j=0+BufferOffset;
        for (int i=0; i<16;i++) {
            bmerge(MICPCMBuffer[0][i], MICPCMBuffer[0][i], &out_data);
            txBuf[j] = out_data;
            txBuf[j+1] = 0;
            bmerge(MICPCMBuffer[1][i], MICPCMBuffer[1][i], &out_data);
            txBuf[j+2] = out_data;
            txBuf[j+3] = 0;
            j+=4;
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
