/******************************************************************************
 * UartTask.c
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
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include <Ifx_reg.h>
#include <UART.h>
#include "Ifx_Types.h"
#include <stdio.h>
#include <string.h>

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

char UART_rxBuf[256];
char UART_txBuf[1024];

/*****************************************************************************/
/*----------------------------Function Prototypes----------------------------*/
/*****************************************************************************/

/*****************************************************************************/
/*-------------------------Function Implementations--------------------------*/
/*****************************************************************************/


static __attribute__((__noreturn__)) void OsTask_UART(void *arg)
{
    (void)arg;

    uint8_t UART_rxBufPtr=0;
    uint16_t infocounter = 0;
    uint32_t printcounter = 0;

    initUART();

    while (1)
    {

        //Check if any data is in the rx queue
        if (receiveUARTCount() > 0) {

            //if yes read the data and put into rx buffer
            int count = receiveUARTCount();
            receiveUARTMessage(&UART_rxBuf[UART_rxBufPtr], (Ifx_SizeT*) &count);
            UART_rxBufPtr+=count;

            //check if user pressed enter - if yes print the line back
            for (int i=0; i<UART_rxBufPtr;i++) {
                if (UART_rxBuf[i] == '\r') {
                    memset(UART_txBuf,0,1024);
                    sprintf(UART_txBuf,"Rx-Msg: %s\r\n",UART_rxBuf);
                    sendUARTMessage(UART_txBuf,strlen(UART_txBuf));
                    UART_rxBufPtr -= (i+1);
                    memset(UART_rxBuf,0,256);
                    break;
                }
            }

        }
        else {

            //send out every 2 secs task-statistics & rx-buf queue size
            if (infocounter == 200) {
                infocounter = 0;
                memset(UART_txBuf,0,1024);
                sprintf (UART_txBuf, "\r\n\r\nTask-Statistics %u - Uart RX Count: %d\r\n", printcounter++, UART_rxBufPtr);
                vTaskGetRunTimeStats(&UART_txBuf[strlen(UART_txBuf)]);
                sendUARTMessage(UART_txBuf,strlen(UART_txBuf));
            }
            else {
                infocounter++;
            }

        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }

}


void UartTaskCreate(void) {

    //Create Task
    xTaskCreate(OsTask_UART, "UART task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);

}
