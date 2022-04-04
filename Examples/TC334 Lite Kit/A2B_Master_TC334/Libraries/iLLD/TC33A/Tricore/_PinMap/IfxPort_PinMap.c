/**
 * \file IfxPort_PinMap.c
 * \brief PORT I/O map
 * \ingroup IfxLld_Port
 *
 * \version iLLD_1_0_1_12_0_1
 * \copyright Copyright (c) 2017 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
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
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#include "IfxPort_PinMap.h"

IfxPort_Pin IfxPort_P00_0 = {&MODULE_P00, 0};
IfxPort_Pin IfxPort_P00_1 = {&MODULE_P00, 1};
IfxPort_Pin IfxPort_P00_10 = {&MODULE_P00,10};
IfxPort_Pin IfxPort_P00_11 = {&MODULE_P00,11};
IfxPort_Pin IfxPort_P00_12 = {&MODULE_P00,12};
IfxPort_Pin IfxPort_P00_2 = {&MODULE_P00, 2};
IfxPort_Pin IfxPort_P00_3 = {&MODULE_P00, 3};
IfxPort_Pin IfxPort_P00_4 = {&MODULE_P00, 4};
IfxPort_Pin IfxPort_P00_5 = {&MODULE_P00, 5};
IfxPort_Pin IfxPort_P00_6 = {&MODULE_P00, 6};
IfxPort_Pin IfxPort_P00_7 = {&MODULE_P00, 7};
IfxPort_Pin IfxPort_P00_8 = {&MODULE_P00, 8};
IfxPort_Pin IfxPort_P00_9 = {&MODULE_P00, 9};
IfxPort_Pin IfxPort_P02_0 = {&MODULE_P02, 0};
IfxPort_Pin IfxPort_P02_1 = {&MODULE_P02, 1};
IfxPort_Pin IfxPort_P02_2 = {&MODULE_P02, 2};
IfxPort_Pin IfxPort_P02_3 = {&MODULE_P02, 3};
IfxPort_Pin IfxPort_P02_4 = {&MODULE_P02, 4};
IfxPort_Pin IfxPort_P02_5 = {&MODULE_P02, 5};
IfxPort_Pin IfxPort_P02_6 = {&MODULE_P02, 6};
IfxPort_Pin IfxPort_P02_7 = {&MODULE_P02, 7};
IfxPort_Pin IfxPort_P02_8 = {&MODULE_P02, 8};
IfxPort_Pin IfxPort_P10_0 = {&MODULE_P10, 0};
IfxPort_Pin IfxPort_P10_1 = {&MODULE_P10, 1};
IfxPort_Pin IfxPort_P10_2 = {&MODULE_P10, 2};
IfxPort_Pin IfxPort_P10_3 = {&MODULE_P10, 3};
IfxPort_Pin IfxPort_P10_4 = {&MODULE_P10, 4};
IfxPort_Pin IfxPort_P10_5 = {&MODULE_P10, 5};
IfxPort_Pin IfxPort_P10_6 = {&MODULE_P10, 6};
IfxPort_Pin IfxPort_P10_7 = {&MODULE_P10, 7};
IfxPort_Pin IfxPort_P10_8 = {&MODULE_P10, 8};
IfxPort_Pin IfxPort_P11_10 = {&MODULE_P11,10};
IfxPort_Pin IfxPort_P11_11 = {&MODULE_P11,11};
IfxPort_Pin IfxPort_P11_12 = {&MODULE_P11,12};
IfxPort_Pin IfxPort_P11_2 = {&MODULE_P11, 2};
IfxPort_Pin IfxPort_P11_3 = {&MODULE_P11, 3};
IfxPort_Pin IfxPort_P11_6 = {&MODULE_P11, 6};
IfxPort_Pin IfxPort_P11_8 = {&MODULE_P11, 8};
IfxPort_Pin IfxPort_P11_9 = {&MODULE_P11, 9};
IfxPort_Pin IfxPort_P13_0 = {&MODULE_P13, 0};
IfxPort_Pin IfxPort_P13_1 = {&MODULE_P13, 1};
IfxPort_Pin IfxPort_P13_2 = {&MODULE_P13, 2};
IfxPort_Pin IfxPort_P13_3 = {&MODULE_P13, 3};
IfxPort_Pin IfxPort_P14_0 = {&MODULE_P14, 0};
IfxPort_Pin IfxPort_P14_1 = {&MODULE_P14, 1};
IfxPort_Pin IfxPort_P14_10 = {&MODULE_P14,10};
IfxPort_Pin IfxPort_P14_2 = {&MODULE_P14, 2};
IfxPort_Pin IfxPort_P14_3 = {&MODULE_P14, 3};
IfxPort_Pin IfxPort_P14_4 = {&MODULE_P14, 4};
IfxPort_Pin IfxPort_P14_5 = {&MODULE_P14, 5};
IfxPort_Pin IfxPort_P14_6 = {&MODULE_P14, 6};
IfxPort_Pin IfxPort_P14_7 = {&MODULE_P14, 7};
IfxPort_Pin IfxPort_P14_8 = {&MODULE_P14, 8};
IfxPort_Pin IfxPort_P14_9 = {&MODULE_P14, 9};
IfxPort_Pin IfxPort_P15_0 = {&MODULE_P15, 0};
IfxPort_Pin IfxPort_P15_1 = {&MODULE_P15, 1};
IfxPort_Pin IfxPort_P15_2 = {&MODULE_P15, 2};
IfxPort_Pin IfxPort_P15_3 = {&MODULE_P15, 3};
IfxPort_Pin IfxPort_P15_4 = {&MODULE_P15, 4};
IfxPort_Pin IfxPort_P15_5 = {&MODULE_P15, 5};
IfxPort_Pin IfxPort_P15_6 = {&MODULE_P15, 6};
IfxPort_Pin IfxPort_P15_7 = {&MODULE_P15, 7};
IfxPort_Pin IfxPort_P15_8 = {&MODULE_P15, 8};
IfxPort_Pin IfxPort_P20_0 = {&MODULE_P20, 0};
IfxPort_Pin IfxPort_P20_1 = {&MODULE_P20, 1};
IfxPort_Pin IfxPort_P20_10 = {&MODULE_P20,10};
IfxPort_Pin IfxPort_P20_11 = {&MODULE_P20,11};
IfxPort_Pin IfxPort_P20_12 = {&MODULE_P20,12};
IfxPort_Pin IfxPort_P20_13 = {&MODULE_P20,13};
IfxPort_Pin IfxPort_P20_14 = {&MODULE_P20,14};
IfxPort_Pin IfxPort_P20_3 = {&MODULE_P20, 3};
IfxPort_Pin IfxPort_P20_6 = {&MODULE_P20, 6};
IfxPort_Pin IfxPort_P20_7 = {&MODULE_P20, 7};
IfxPort_Pin IfxPort_P20_8 = {&MODULE_P20, 8};
IfxPort_Pin IfxPort_P20_9 = {&MODULE_P20, 9};
IfxPort_Pin IfxPort_P21_0 = {&MODULE_P21, 0};
IfxPort_Pin IfxPort_P21_1 = {&MODULE_P21, 1};
IfxPort_Pin IfxPort_P21_2 = {&MODULE_P21, 2};
IfxPort_Pin IfxPort_P21_3 = {&MODULE_P21, 3};
IfxPort_Pin IfxPort_P21_4 = {&MODULE_P21, 4};
IfxPort_Pin IfxPort_P21_5 = {&MODULE_P21, 5};
IfxPort_Pin IfxPort_P21_6 = {&MODULE_P21, 6};
IfxPort_Pin IfxPort_P21_7 = {&MODULE_P21, 7};
IfxPort_Pin IfxPort_P22_0 = {&MODULE_P22, 0};
IfxPort_Pin IfxPort_P22_1 = {&MODULE_P22, 1};
IfxPort_Pin IfxPort_P22_2 = {&MODULE_P22, 2};
IfxPort_Pin IfxPort_P22_3 = {&MODULE_P22, 3};
IfxPort_Pin IfxPort_P22_4 = {&MODULE_P22, 4};
IfxPort_Pin IfxPort_P23_1 = {&MODULE_P23, 1};
IfxPort_Pin IfxPort_P23_5 = {&MODULE_P23, 5};
IfxPort_Pin IfxPort_P32_4 = {&MODULE_P32, 4};
IfxPort_Pin IfxPort_P33_0 = {&MODULE_P33, 0};
IfxPort_Pin IfxPort_P33_1 = {&MODULE_P33, 1};
IfxPort_Pin IfxPort_P33_10 = {&MODULE_P33,10};
IfxPort_Pin IfxPort_P33_11 = {&MODULE_P33,11};
IfxPort_Pin IfxPort_P33_12 = {&MODULE_P33,12};
IfxPort_Pin IfxPort_P33_2 = {&MODULE_P33, 2};
IfxPort_Pin IfxPort_P33_3 = {&MODULE_P33, 3};
IfxPort_Pin IfxPort_P33_4 = {&MODULE_P33, 4};
IfxPort_Pin IfxPort_P33_5 = {&MODULE_P33, 5};
IfxPort_Pin IfxPort_P33_6 = {&MODULE_P33, 6};
IfxPort_Pin IfxPort_P33_7 = {&MODULE_P33, 7};
IfxPort_Pin IfxPort_P33_8 = {&MODULE_P33, 8};
IfxPort_Pin IfxPort_P33_9 = {&MODULE_P33, 9};
IfxPort_Pin IfxPort_P34_1 = {&MODULE_P34, 1};
IfxPort_Pin IfxPort_P34_2 = {&MODULE_P34, 2};
IfxPort_Pin IfxPort_P34_3 = {&MODULE_P34, 3};
IfxPort_Pin IfxPort_P40_4 = {&MODULE_P40, 4};
IfxPort_Pin IfxPort_P40_5 = {&MODULE_P40, 5};
IfxPort_Pin IfxPort_P40_6 = {&MODULE_P40, 6};
IfxPort_Pin IfxPort_P40_7 = {&MODULE_P40, 7};
IfxPort_Pin IfxPort_P40_8 = {&MODULE_P40, 8};
IfxPort_Pin IfxPort_P40_9 = {&MODULE_P40, 9};


const IfxPort_Pin *IfxPort_Pin_pinTable[IFXPORT_PINMAP_NUM_MODULES][IFXPORT_PINMAP_PIN_NUM_ITEMS] = {
    {
        &IfxPort_P00_0,
        &IfxPort_P00_1,
        &IfxPort_P00_2,
        &IfxPort_P00_3,
        &IfxPort_P00_4,
        &IfxPort_P00_5,
        &IfxPort_P00_6,
        &IfxPort_P00_7,
        &IfxPort_P00_8,
        &IfxPort_P00_9,
        &IfxPort_P00_10,
        &IfxPort_P00_11,
        &IfxPort_P00_12,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        &IfxPort_P02_0,
        &IfxPort_P02_1,
        &IfxPort_P02_2,
        &IfxPort_P02_3,
        &IfxPort_P02_4,
        &IfxPort_P02_5,
        &IfxPort_P02_6,
        &IfxPort_P02_7,
        &IfxPort_P02_8,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        &IfxPort_P10_0,
        &IfxPort_P10_1,
        &IfxPort_P10_2,
        &IfxPort_P10_3,
        &IfxPort_P10_4,
        &IfxPort_P10_5,
        &IfxPort_P10_6,
        &IfxPort_P10_7,
        &IfxPort_P10_8,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        &IfxPort_P11_2,
        &IfxPort_P11_3,
        NULL_PTR,
        NULL_PTR,
        &IfxPort_P11_6,
        NULL_PTR,
        &IfxPort_P11_8,
        &IfxPort_P11_9,
        &IfxPort_P11_10,
        &IfxPort_P11_11,
        &IfxPort_P11_12,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        &IfxPort_P13_0,
        &IfxPort_P13_1,
        &IfxPort_P13_2,
        &IfxPort_P13_3,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        &IfxPort_P14_0,
        &IfxPort_P14_1,
        &IfxPort_P14_2,
        &IfxPort_P14_3,
        &IfxPort_P14_4,
        &IfxPort_P14_5,
        &IfxPort_P14_6,
        &IfxPort_P14_7,
        &IfxPort_P14_8,
        &IfxPort_P14_9,
        &IfxPort_P14_10,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        &IfxPort_P15_0,
        &IfxPort_P15_1,
        &IfxPort_P15_2,
        &IfxPort_P15_3,
        &IfxPort_P15_4,
        &IfxPort_P15_5,
        &IfxPort_P15_6,
        &IfxPort_P15_7,
        &IfxPort_P15_8,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        &IfxPort_P20_0,
        &IfxPort_P20_1,
        NULL_PTR,
        &IfxPort_P20_3,
        NULL_PTR,
        NULL_PTR,
        &IfxPort_P20_6,
        &IfxPort_P20_7,
        &IfxPort_P20_8,
        &IfxPort_P20_9,
        &IfxPort_P20_10,
        &IfxPort_P20_11,
        &IfxPort_P20_12,
        &IfxPort_P20_13,
        &IfxPort_P20_14
    },
    {
        &IfxPort_P21_0,
        &IfxPort_P21_1,
        &IfxPort_P21_2,
        &IfxPort_P21_3,
        &IfxPort_P21_4,
        &IfxPort_P21_5,
        &IfxPort_P21_6,
        &IfxPort_P21_7,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        &IfxPort_P22_0,
        &IfxPort_P22_1,
        &IfxPort_P22_2,
        &IfxPort_P22_3,
        &IfxPort_P22_4,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        &IfxPort_P23_1,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        &IfxPort_P23_5,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        &IfxPort_P32_4,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        &IfxPort_P33_0,
        &IfxPort_P33_1,
        &IfxPort_P33_2,
        &IfxPort_P33_3,
        &IfxPort_P33_4,
        &IfxPort_P33_5,
        &IfxPort_P33_6,
        &IfxPort_P33_7,
        &IfxPort_P33_8,
        &IfxPort_P33_9,
        &IfxPort_P33_10,
        &IfxPort_P33_11,
        &IfxPort_P33_12,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        &IfxPort_P34_1,
        &IfxPort_P34_2,
        &IfxPort_P34_3,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        &IfxPort_P40_4,
        &IfxPort_P40_5,
        &IfxPort_P40_6,
        &IfxPort_P40_7,
        &IfxPort_P40_8,
        &IfxPort_P40_9,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    }
};
