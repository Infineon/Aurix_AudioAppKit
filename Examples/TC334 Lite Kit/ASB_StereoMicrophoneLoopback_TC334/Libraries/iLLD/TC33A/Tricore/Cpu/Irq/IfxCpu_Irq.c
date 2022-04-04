/**
 * \file IfxCpu_Irq.c
 * \brief This file contains the APIs for Interrupt related functions.
 *
 *
 * \version iLLD_1_0_1_12_0_1
 * \copyright Copyright (c) 2019 Infineon Technologies AG. All rights reserved.
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
 *
 */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Cpu/Irq/IfxCpu_Irq.h"
#include "Tricore/Compilers/Compilers.h"
#include "Cpu/Std/IfxCpu_Intrinsics.h"
#include "IfxCpu_reg.h"

/*******************************************************************************
**                      Private macros                                        **
*******************************************************************************/

/*******************************************************************************
**                       Global variables/constants                           **
*******************************************************************************/
#if defined(IFX_USE_SW_MANAGED_INT)

typedef void (*Ifx_Isr)(void);

BEGIN_DATA_SECTION(.bss_cpu0)
static Ifx_Isr IfxCpu_Irq_swIntVector0[256];
END_DATA_SECTION

#ifndef IFX_CFG_CPU_IRQ_DEBUG
 #define IFX_CFG_CPU_IRQ_DEBUG __debug()
#endif

#endif /*defined(IFX_USE_SW_MANAGED_INT) */

/*******************************************************************************
**                      Global Function definitions                          **
*******************************************************************************/
#if defined(IFX_USE_SW_MANAGED_INT)

/** \brief API to install the interrupt service routine for Software Managed Interrupts.
 *
 */
void IfxCpu_Irq_installInterruptHandler(void *isrFuncPointer, uint32 serviceReqPrioNumber)
{
	switch (IfxCpu_Irq_getTos(IfxCpu_getCoreIndex()))
    {
    case IfxSrc_Tos_cpu0:
        IfxCpu_Irq_swIntVector0[serviceReqPrioNumber] = (Ifx_Isr)isrFuncPointer;
        break;
    case IfxSrc_Tos_dma:
    	break;
    default:
    	break;
    }
}


/** SW managed Interrupt vector tables
 *
 * These are vector tables with single entry for Software Managed Interrupts defined for each core.
 * This function need to be located at boundary 0xXFE0 where (X=1,3,5 and so on). For the software managed
 * interrupts to work correctly, the BIV must be set to address of this function.
 *
 */
IFX_INTERRUPT_INTERNAL(IfxCpu_Irq_intVecTable0, 0, 255)
{
    Ifx_CPU_ICR icr;

    icr.U = __mfcr(CPU_ICR);    /*Fetch the ICR value */

    /*Call the ISR */
    if(IfxCpu_Irq_swIntVector0[icr.B.CCPN])
    {
        IfxCpu_Irq_swIntVector0[icr.B.CCPN]();
    }
    else
    {
    	IFX_CFG_CPU_IRQ_DEBUG;
    }
}


#endif /*defined(IFX_USE_SW_MANAGED_INT) */

/** \brief API to get type of service of the caller CPU.
 *
 */
IfxSrc_Tos IfxCpu_Irq_getTos(IfxCpu_ResourceCpu coreId)
{
    const IfxSrc_Tos tos[IFXCPU_NUM_MODULES] = {
        IfxSrc_Tos_cpu0
    };

    return tos[coreId];
}
