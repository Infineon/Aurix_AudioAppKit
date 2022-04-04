/******************************************************************************
 * ArrayBoardLedTask.h
 * Copyright (C) Infineon Technologies AG 2022
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




#ifndef ArrayBoardLedTask
#define ArrayBoardLedTask

/*****************************************************************************/
/*----------------------------------Includes---------------------------------*/
/*****************************************************************************/

#include <stdint.h>

/*****************************************************************************/
/*-----------------------------------Macros----------------------------------*/
/*****************************************************************************/

#define LED0        P33_OUT.B.P11
#define LED1        P33_OUT.B.P12
#define LED2        P33_OUT.B.P13
#define LED3        P23_OUT.B.P1
#define LED4        P23_OUT.B.P0
#define LED5        P23_OUT.B.P3
#define LED6        P23_OUT.B.P2
#define LED7        P22_OUT.B.P1
#define LED8        P22_OUT.B.P0
#define LED9        P21_OUT.B.P0
#define LED10       P22_OUT.B.P2
#define LED11       P21_OUT.B.P4
#define LEDINFO0    P21_OUT.B.P5
#define LEDINFO1    P20_OUT.B.P1
#define LEDINFO2    P15_OUT.B.P5

/*****************************************************************************/
/*------------------------------Global variables-----------------------------*/
/*****************************************************************************/

/*****************************************************************************/
/*-------------------------------Data Structures-----------------------------*/
/*****************************************************************************/

/*****************************************************************************/
/*-------------------------Global Variables/Constants------------------------*/
/*****************************************************************************/

/*****************************************************************************/
/*----------------------------Function Prototypes----------------------------*/
/*****************************************************************************/

void InitArrayBoardLedTask(void);


/*****************************************************************************/
/*----------------------Inline Function Implementations----------------------*/
/*****************************************************************************/


#endif /* ArrayBoardLedTask */
