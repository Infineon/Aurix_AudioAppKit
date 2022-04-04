/******************************************************************************
 * Audio.c
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

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "Ifx_reg.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "IfxStm.h"
#include "ADI_DEV_CFG.h"
#include "i2c0_public.h"
#include "ports.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
/*****************************************************************************/
/*-----------------------------------Macros----------------------------------*/
/*****************************************************************************/

/*****************************************************************************/
/*------------------------------Global variables-----------------------------*/
/*****************************************************************************/

//Audio RX/TX Buffer
int32_t __attribute__ ((__align(4*1024))) rxBuf[4096];
int32_t __attribute__ ((__align(4*1024))) txBuf[4096];

/*****************************************************************************/
/*-------------------------------Data Structures-----------------------------*/
/*****************************************************************************/

/*****************************************************************************/
/*-------------------------Private Variables/Constants-----------------------*/
/*****************************************************************************/
char i2c_data_buf[1500];
/*****************************************************************************/
/*----------------------------Function Prototypes----------------------------*/
/*****************************************************************************/

/*****************************************************************************/
/*-------------------------Function Implementations--------------------------*/
/*****************************************************************************/




/*
 * Inits the I²C peripheral for communication to A2B-Chip / Codec
 */

void Init_A2B_Codec(void) {

    I2C0_Init();



    for (int i=0; i<CONFIG_LEN; i++) {


        //wait if delay is needed
        if (gaA2BConfig[i].eOpCode == DELAY) {
            uint32_t msecs = 0;

            for (int j=0; j<gaA2BConfig[i].nDataCount; j++) {
                msecs += gaA2BConfig[i].paConfigData[j];
            }

            vTaskDelay(pdMS_TO_TICKS(msecs));

        }

        //write config
        else if (gaA2BConfig[i].eOpCode == WRITE) {


            //write a2b config
            if (gaA2BConfig[i].nAddrWidth==1) {

                //read dev address
                uint8_t i2c_addr = gaA2BConfig[i].nDeviceAddr;

                //set internal reg address
                i2c_data_buf[0] = gaA2BConfig[i].nAddr&0xFF;

                //copy reg-data into buffer
                memcpy(&i2c_data_buf[1], gaA2BConfig[i].paConfigData, gaA2BConfig[i].nDataCount);

                //transmit
                I2C0_Write(i2c_addr, i2c_data_buf, (uint16) gaA2BConfig[i].nDataCount+1);
            }


            //write adau1761 config
            if (gaA2BConfig[i].nAddrWidth==2) {

                //read dev address
                uint8_t i2c_addr = gaA2BConfig[i].nDeviceAddr;

                //set internal reg address
                i2c_data_buf[0] = (gaA2BConfig[i].nAddr>>8)&0xFF;
                i2c_data_buf[1] = (gaA2BConfig[i].nAddr)&0xFF;

                //copy reg-data into buffer
                memcpy(&i2c_data_buf[2],gaA2BConfig[i].paConfigData,gaA2BConfig[i].nDataCount);

                //transmit
                I2C0_Write(i2c_addr, i2c_data_buf, (uint16) gaA2BConfig[i].nDataCount+2);
            }
        }


        //read a2b config
        else if (gaA2BConfig[i].eOpCode == READ && gaA2BConfig[i].nAddrWidth==1) {

            //not implemented as it is not needed
        }

    }


}


/*
 * Set the data-input mux to switch TDM data-in (to Aurix) between A²B or Line-In from Audio-Codec
 * mux=1 -> A²B input used
 * mux=0 -> Line-In from Codec used
 */

void Set_TDM_DataIn_Mux(uint8_t mux) {

    //Init P10.5 to output to set pin to high/low
    P10_IOCR4.B.PC5 = 0x10;
    P10_OUT.B.P5 = mux;

}

/*
 * This function initializes the I²S emulation based on QSPI/GTM. Data I/O is operated by DMA in double-buffering mode.
 * The RX/TX buffer sizes are fixed to 2*2048 words buffer (32-Bit)
 */
void TDM8_Init_DMA(void) {




    /*
     * inits the GTM together with QSPI (Slave-Mode) to make a TDM master-interface.
     *
     * P2.4 -> QSPI3_SLSIA -> QSPI sync input
     * P2.5 -> QSPI3_MRST -> QSPI Slave data output (TDM data out)
     * P2.6 -> QSPI3_MTSRA -> QSPI Slave data input (TDM data in)
     * P2.7 -> QSPI_SCLKA -> QSPI Slave clock input (negative phase BCLK)
     *
     *
     * Hint: Mentioned frequencies below are only as example for 48 kHz mode
     *
     * P2.0 -> GTM_TIM0CH0 -> 24.576 MHz reference clock input from Oscillator
     * P2.1 -> GTM_TOUT1 / TOM0CH9 -> 12.288 MHz TDM MCLK output
     * P2.3 -> GTM_TOUT3 / TOM0CH11 -> QSPI-Sync output -> for syncing qspi module to TDM clocking
     * P10.1 -> GTM_TOUT103 / TOM0CH1 -> 12.288 MHz TDM BCLK output
     * P10.2 -> GTM_TOUT104 / TOM0CH2 -> 12.288 MHz TDM Inverted BCLK output (for clocking QSPI module)
     * P10.3 -> GTM_TOUT105 / TOM0CH3 -> 48kHz LRCLK output
     *
     *
     *
     * QSPI_SCKLA must be directly connected to Inverted BCLK output (P10.2 -> P2.7)
     * QSPI_SLSIA must be connected with QSPI-sync output (P2.3 -> P2.4)
     *
     * TDM Format = 256 cycles per WCLK cycle = 8*32 bit framing
     * TDM MCLK output -> P2.1  -> 12.288 MHz
     * TDM BCLK output -> P10.1 -> 12.288 MHz
     * TDM WCLK output -> P10.3 -> 48 kHz
     * TDM data in (from external ADC) P2.6
     * TDM data out (to external DAC) P2.5
     *
     * P2.0 must be supplied with an external 24.576 MHz reference clock (from clock generator / oscillator etc)
     *
     *
     *
     */







    IfxScuWdt_clearCpuEndinit(IfxScuWdt_getCpuWatchdogPassword ());






    /*
     * ---------------------------------------------------------------------------------------------------------------
     * Pre-Init of IO's
     * ---------------------------------------------------------------------------------------------------------------
     */

    //before starting GTM let's keep all outputs on high output level first
    P02_OUT.B.P1 = 1;
    P02_OUT.B.P3 = 1;
    P10_OUT.B.P1 = 1;
    P10_OUT.B.P2 = 1;
    P10_OUT.B.P3 = 1;


    //Switch the five GTM output ports to static GPIO to signal the high-levels
    P02_IOCR0.B.PC1 = 0x10;
    P02_IOCR0.B.PC3 = 0x10;
    P10_IOCR0.B.PC1 = 0x10;
    P10_IOCR0.B.PC2 = 0x10;
    P10_IOCR0.B.PC3 = 0x10;


    //set all outputs to fastest edge possible
    P02_PDR0.B.PD1 = 0x0; //mclk
    P02_PDR0.B.PD3 = 0x0; //wclk
    P10_PDR0.B.PD1 = 0x0; //bclk
    P10_PDR0.B.PD2 = 0x0; //bclk inv
    P10_PDR0.B.PD3 = 0x0; //sync









    /*
     * ---------------------------------------------------------------------------------------------------------------
     * Init of QSPI module
     * ---------------------------------------------------------------------------------------------------------------
     */

    //Enable clock of QSPI3 module
    QSPI3_CLC.B.DISR    = 0;
    while(0 != QSPI3_CLC.U);

    //fastest edge for QSPI output
    P02_PDR0.B.PD5      = 0x0;
    //set output P02.5 to QSPI data slave out
    P02_IOCR4.B.PC5     = 0x13;

    //QSPI slave clock A selected
    QSPI3_PISEL.B.SCIS  = 0x0;
    //QSPI slave select input A selected
    QSPI3_PISEL.B.SLSIS = 0x1;



    QSPI3_GLOBALCON.B.EXPECT        = 15;                 //timeout to highest value
    QSPI3_GLOBALCON.B.SRF           = 0;                  //STOP of RxFIFO full -> No
    QSPI3_GLOBALCON.B.MS            = 0;                  //Select QSPI master mode for configuration -> switch later back to slave
    QSPI3_GLOBALCON.B.LB            = 0;                  //Loopback off
    QSPI3_GLOBALCON.B.CLKSEL        = 1;                  //fper = clk



    QSPI3_GLOBALCON1.B.RXEN         = 0x1;                //Configure RX Interrupt
    QSPI3_GLOBALCON1.B.RXFM         = 0x2;
    QSPI3_GLOBALCON1.B.RXFIFOINT    = 0x1;

    QSPI3_GLOBALCON1.B.TXEN         = 0x1;                //Configure TX Interrupt
    QSPI3_GLOBALCON1.B.RXFM         = 0x1;
    QSPI3_GLOBALCON1.B.TXFIFOINT    = 0x3;

    QSPI3_GLOBALCON1.B.ERRORENS     = 0x1ff;


    QSPI3_GLOBALCON.B.MS            = 2;                  //now enable slave mode
    QSPI3_GLOBALCON.B.EN            = 1;                  //RUN mode requested



    //BACON configuration for QSPI
    /*
     * Not last data word -> for QSPI continuous streaming mode
     * DataLength = 32 bit
     * Type = MSB First
     */
    uint32_t BACON0 =  ( (0x1 << 21 ) | (0 << 22) | (31 << 23) | (0x0 << 28)|(0<<0));

    QSPI3_BACONENTRY.U = BACON0;


    //Prefil TXFIFO
    QSPI3_DATAENTRY0.U = 0x0;
    QSPI3_DATAENTRY0.U = 0x0;
    QSPI3_DATAENTRY0.U = 0x0;
    QSPI3_DATAENTRY0.U = 0x0;


    //Route QSPI RX/TX signals to DMA channel 49+50
    SRC_QSPI3RX.B.SRPN  = 50; //interrupt ID 50
    SRC_QSPI3RX.B.TOS   = 1;  //route to DMA
    SRC_QSPI3RX.B.SRE   = 1;  //enable


    SRC_QSPI3TX.B.SRPN  = 49; //interrupt ID 49
    SRC_QSPI3TX.B.TOS   = 1;  //route to DMA
    SRC_QSPI3TX.B.SRE   = 1;  //enable













    /*
     * ---------------------------------------------------------------------------------------------------------------
     * Init of DMA
     * ---------------------------------------------------------------------------------------------------------------
     */


    //Init DMA for RX-Channel (DMA channel 50)

    //define rx dma source
    DMA_SADR050.U           = (uint32) &QSPI3_RXEXIT.U;
    DMA_ADICR050.B.SCBE     = 1; /* Enable source circular buffer */
    DMA_ADICR050.B.CBLS     = 0; /* Source address SADR[31:0] is not updated ie same source address will be used for all transfers */
    DMA_ADICR050.B.WRPSE    = 0; /* Disable wrap source buffer interrupt */

    //define rx dma destination
    DMA_ADICR050.B.SHCT     = 0xb; /* Shadow control: Destination double-buffering with automatic switch */
    DMA_DADR050.U           = (uint32) &rxBuf[0]; //address of first buffer half
    DMA_SHADR050.U          = (uint32) &rxBuf[2048]; //address of second buffer half
    DMA_ADICR050.B.DMF      = 0; /* Destination address modified by 1x CHDW */
    DMA_ADICR050.B.INCD     = 1; /* Increment destination address automatically */
    DMA_ADICR050.B.DCBE     = 1; /* Enable destination circular buffer */
    DMA_ADICR050.B.WRPDE    = 1; /* Enable wrap destination buffer interrupt */
    DMA_ADICR050.B.CBLD     = 13; /* 2048 (32-bit) words per single buffer */

    DMA_ADICR050.B.STAMP    = 0; /* Disable timestamp */


    DMA_CHCFGR050.B.TREL    = 2048; /* Transfer count reload value: 2048 words per buffer */
    DMA_CHCFGR050.B.BLKM    = 0;  /* 1 dma move executed per transfer */
    DMA_CHCFGR050.B.RROAT   = 0;  /* One transfer per trigger */
    DMA_CHCFGR050.B.CHMODE  = 1;  /* Cont. Transaction Mode */
    DMA_CHCFGR050.B.CHDW    = 2;  /* Channel Data Width is 32 bit */
    DMA_CHCFGR050.B.PATSEL  = 0;  /* Pattern detection disabled */
    DMA_CHCFGR050.B.PRSEL   = 0;  /* Peripheral trigger selected */

    DMA_TSR050.B.ECH        = 1; /* Enable Hardware Channel Requests */



    //Init DMA for TX-Channel (DMA channel 49)

    //define tx dma source
    DMA_ADICR049.B.SHCT     = 0x9; /* Shadow control: Source double-buffering with automatic switch */
    DMA_SADR049.U           = (uint32) &txBuf[0];
    DMA_SHADR049.U          = (uint32) &txBuf[2048];

    //define tx dma destination
    DMA_DADR049.U           = (uint32) &QSPI3_DATAENTRY0.U;
    DMA_ADICR049.B.DCBE     = 1; /* Enable destination circular buffer */
    DMA_ADICR049.B.CBLD     = 0; /* circular buffer length destination is 0 - always same address */
    DMA_ADICR049.B.WRPDE    = 0; /* Disable wrap destination buffer interrupt */

    DMA_ADICR049.B.SMF      = 0; /* source address modified by 1x CHDW */
    DMA_ADICR049.B.INCS     = 1; /* Increment source address automatically */
    DMA_ADICR049.B.SCBE     = 1; /* Enable source circular buffer */
    DMA_ADICR049.B.WRPSE    = 1; /* Enable wrap source buffer interrupt */
    DMA_ADICR049.B.CBLS     = 13; /* 2048 (32-bit) words per single buffer */

    DMA_ADICR049.B.STAMP    = 0;  /* Disable timestamp */

    DMA_CHCFGR049.B.TREL    = 2048; /* Transfer count reload value: 2048 words per buffer */
    DMA_CHCFGR049.B.BLKM    = 0;  /* 1 dma move executed per transfer */
    DMA_CHCFGR049.B.RROAT   = 0;  /* One transfer per trigger */
    DMA_CHCFGR049.B.CHMODE  = 1;  /* Cont. Transaction Mode */
    DMA_CHCFGR049.B.CHDW    = 2;  /* Channel Data Width is 32 bit */
    DMA_CHCFGR049.B.PATSEL  = 0;  /* Pattern detection disabled */
    DMA_CHCFGR049.B.PRSEL   = 0;  /* Daisy-Chain trigger selected */
    DMA_ADICR049.B.WRPSE    = 1;  /* Enable wrap source buffer interrupt */

    DMA_TSR049.B.ECH        = 1;  /* Enable Hardware Channel Requests */




    //The RX-DMA will trigger an interrupt to CPU0 on ISR-ID 30.
    //As the QSPI is bidirectional, RX-DMA and TX-DMA are in fact synchronous.
    //Therefore, it is sufficient to handle ISR from RX-DMA (is at the same timepoint as TX-DMA would trigger the interrupt)

    SRC_DMACH50.B.SRPN      = 30; //interrupt ID 30
    SRC_DMACH50.B.TOS       = 0; //route to CPU0
    SRC_DMACH50.B.SRE       = 1; //enable








    /*
     * ---------------------------------------------------------------------------------------------------------------
     * Init of GTM
     * ---------------------------------------------------------------------------------------------------------------
     */


    //Init GTM clk
    GTM_CLC.U = 0;
    GTM_CMU_CLK_EN.B.EN_FXCLK = 0x0;

    //RUN GTM clusters as fast as possible
    GTM_CTRL.B.RF_PROT = 0;
    GTM_CLS_CLK_CFG.B.CLS0_CLK_DIV = 1;
    GTM_CLS_CLK_CFG.B.CLS1_CLK_DIV = 1;


    /*
     * Configure TOM0CH0 to route TIM_EXT_CAPTURE(X) signal into the TRIG(X) daisy-chain
     */
    //USE TIM_EXT_CAPTURE(X) signal if ECLK_SRC==1
    GTM_TOM0_CH0_CTRL.B.CLK_SRC_SR = 6;
    GTM_TOM0_CH0_CTRL.B.ECLK_SRC = 1;
    //TIM_EXT_CAPTURE(x) signal used as output on TRIG_(x) chain (if trigout==0)
    GTM_TOM0_CH0_CTRL.B.EXTTRIGOUT = 1;
    GTM_TOM0_CH0_CTRL.B.TRIGOUT=0;



    /*
     * GTM TOUT Mapping
     *
     */

    //TOUT1 (P02.1) to TOM0CH9
    GTM_TOUTSEL0.B.SEL1 = 0;

    //TOUT3 (P02.3) to TOM0CH11
    GTM_TOUTSEL0.B.SEL3 = 0;

    //TOUT103 (P10.1) to TOM0CH1
    GTM_TOUTSEL12.B.SEL7 = 0;

    //TOUT104 (P10.2) to TOM0CH2
    GTM_TOUTSEL13.B.SEL0 = 0;

    //TOUT105 (P10.3) to TOM0CH3
    GTM_TOUTSEL13.B.SEL1 = 0;



    /*
     * Configure TOM0CH1 which is BCLK (normal phase) -> divide CLKINPUT/8 -> 24.576/2 = 12.288 MHz
     * Clocking derived from TRIG_(x) chain
     */
    GTM_TOM0_CH1_CN0.U = 0;
    GTM_TOM0_CH1_SR0.U = 2;
    GTM_TOM0_CH1_SR1.U = 1;
    GTM_TOM0_CH1_CM0.U = GTM_TOM0_CH1_SR0.U;
    GTM_TOM0_CH1_CM1.U = GTM_TOM0_CH1_SR1.U;
    GTM_TOM0_CH1_CTRL.U = 0;
    GTM_TOM0_CH1_CTRL.B.CLK_SRC_SR = 5;
    GTM_TOM0_CH1_CTRL.B.ECLK_SRC = 1;
    GTM_TOM0_CH1_CTRL.B.SL = 1;
    GTM_TOM0_CH1_CTRL.B.OSM = 0;
    GTM_TOM0_TGC0_OUTEN_CTRL.B.OUTEN_CTRL1 = 0x2;
    GTM_TOM0_TGC0_ENDIS_CTRL.B.ENDIS_CTRL1 = 2;
    GTM_TOM0_TGC0_FUPD_CTRL.B.FUPD_CTRL1 = 2;
    GTM_TOM0_TGC0_GLB_CTRL.B.UPEN_CTRL1 = 2;


    /*
     * Configure TOM0CH2 which is BCLK inverted -> divide CLKINPUT/8 -> 24.576/2 = 12.288 MHz with offset of 1 = 180° shift
     * Clocking derived from TRIG_(x) chain
     */
    GTM_TOM0_CH2_CN0.U = 1;
    GTM_TOM0_CH2_SR0.U = 2;
    GTM_TOM0_CH2_SR1.U = 1;
    GTM_TOM0_CH2_CM0.U = GTM_TOM0_CH2_SR0.U;
    GTM_TOM0_CH2_CM1.U = GTM_TOM0_CH2_SR1.U;
    GTM_TOM0_CH2_CTRL.U = 0;
    GTM_TOM0_CH2_CTRL.B.CLK_SRC_SR = 5;
    GTM_TOM0_CH2_CTRL.B.ECLK_SRC = 1;
    GTM_TOM0_CH2_CTRL.B.SL = 1;
    GTM_TOM0_CH2_CTRL.B.OSM = 0;
    GTM_TOM0_TGC0_OUTEN_CTRL.B.OUTEN_CTRL2 = 0x2;
    GTM_TOM0_TGC0_ENDIS_CTRL.B.ENDIS_CTRL2 = 2;
    GTM_TOM0_TGC0_FUPD_CTRL.B.FUPD_CTRL2 = 2;
    GTM_TOM0_TGC0_GLB_CTRL.B.UPEN_CTRL2 = 2;


    /*
     * Configure TOM0CH3 which is LRCLK -> divide CLKINPUT/512 -> 24.576/512 = 48 kHz with 180°phase relation to BCLK
     * Clocking derived from TRIG_(x) chain
     */
    GTM_TOM0_CH3_CN0.U = 0;
    GTM_TOM0_CH3_SR0.U = 512;
    GTM_TOM0_CH3_SR1.U = 256;
    GTM_TOM0_CH3_CM0.U = GTM_TOM0_CH3_SR0.U;
    GTM_TOM0_CH3_CM1.U = GTM_TOM0_CH3_SR1.U;
    GTM_TOM0_CH3_CTRL.U = 0;
    GTM_TOM0_CH3_CTRL.B.CLK_SRC_SR = 5;
    GTM_TOM0_CH3_CTRL.B.ECLK_SRC = 1;
    GTM_TOM0_CH3_CTRL.B.SL = 1;
    GTM_TOM0_CH3_CTRL.B.OSM = 0;
    GTM_TOM0_TGC0_OUTEN_CTRL.B.OUTEN_CTRL3 = 0x2;
    GTM_TOM0_TGC0_ENDIS_CTRL.B.ENDIS_CTRL3 = 2;
    GTM_TOM0_TGC0_FUPD_CTRL.B.FUPD_CTRL3 = 2;
    GTM_TOM0_TGC0_GLB_CTRL.B.UPEN_CTRL3 = 2;


    /*
     * Configure TOM0CH9 which is MCLK -> divide CLKINPUT/2 -> 24.576/2 = 12.288 MHz
     * Clocking derived from TRIG_(x) chain
     */
    GTM_TOM0_CH9_CN0.U = 0;
    GTM_TOM0_CH9_SR0.U = 2;
    GTM_TOM0_CH9_SR1.U = 1;
    GTM_TOM0_CH9_CM0.U = GTM_TOM0_CH9_SR0.U;
    GTM_TOM0_CH9_CM1.U = GTM_TOM0_CH9_SR1.U;
    GTM_TOM0_CH9_CTRL.U = 0;
    GTM_TOM0_CH9_CTRL.B.CLK_SRC_SR = 5;
    GTM_TOM0_CH9_CTRL.B.ECLK_SRC = 1;
    GTM_TOM0_CH9_CTRL.B.SL = 1;
    GTM_TOM0_CH9_CTRL.B.OSM = 0;
    GTM_TOM0_TGC1_OUTEN_CTRL.B.OUTEN_CTRL1 = 0x2;
    GTM_TOM0_TGC1_ENDIS_CTRL.B.ENDIS_CTRL1 = 2;
    GTM_TOM0_TGC1_FUPD_CTRL.B.FUPD_CTRL1 = 2;
    GTM_TOM0_TGC1_GLB_CTRL.B.UPEN_CTRL1 = 2;


    /*
     * Configure TOM0CH11 which is the QSPI Sync
     * Clocking derived from TRIG_(x) chain
     * This TOM is configured as one-shot (single high-to-low transition) to synchronize to QSPI module to the TDM clocking.
     * The one-shot high-time must be carefully chosen to exactly align with a rising TDM-WCLK-edge
     */
    uint16 slsival = 512;       //wait one WCLK cycle to start QSPI operation
    GTM_TOM0_CH11_SR0.U = slsival;
    GTM_TOM0_CH11_SR1.U = 10000;
    GTM_TOM0_CH11_CM0.U = slsival;
    GTM_TOM0_CH11_CM1.U = 10000;

    GTM_TOM0_CH11_CTRL.U = 0;
    GTM_TOM0_CH11_CTRL.B.FREEZE = 1;
    GTM_TOM0_CH11_CTRL.B.CLK_SRC_SR = 5;
    GTM_TOM0_CH11_CTRL.B.ECLK_SRC = 1;
    GTM_TOM0_CH11_CTRL.B.SL = 0;
    GTM_TOM0_CH11_CTRL.B.OSM = 1;
    GTM_TOM0_TGC1_OUTEN_CTRL.B.OUTEN_CTRL3 = 0x2;
    GTM_TOM0_TGC1_ENDIS_CTRL.B.ENDIS_CTRL3 = 2;
    GTM_TOM0_TGC1_FUPD_CTRL.B.FUPD_CTRL3 = 2;
    GTM_TOM0_TGC1_GLB_CTRL.B.UPEN_CTRL3 = 2;



    //Start GTM clocks
    GTM_CMU_CLK_EN.B.EN_FXCLK = 0x2;


    //trigger the TOM0 cluster
    GTM_TOM0_TGC0_GLB_CTRL.U |= 0x1;
    GTM_TOM0_TGC1_GLB_CTRL.U |= 0x1;


    //trigger the SYNC one-shot timer
    GTM_TOM0_CH11_CN0.U = 0;


    //Select P02.0 as input for TIM0CH0
    GTM_TIM0INSEL.B.CH0SEL              = 2;

    //Use TIM_IN(x) as input channel if CICTRL==1
    GTM_TIM0_CH0_CTRL.B.CICTRL          = 1;
    GTM_TIM0_CH0_ECTRL.B.EXT_CAP_SRC    = 0x3;

    //Enable external capture
    GTM_TIM0_CH0_CTRL.B.EXT_CAP_EN      = 1;








    /*
     * ---------------------------------------------------------------------------------------------------------------
     * hand over clocking-pins to GTM
     * ---------------------------------------------------------------------------------------------------------------
     */
    P10_IOCR0.B.PC3 = 0x11;
    P02_IOCR0.B.PC1 = 0x11;
    P02_IOCR0.B.PC3 = 0x11;
    P10_IOCR0.B.PC1 = 0x11;
    P10_IOCR0.B.PC2 = 0x11;






     //now the TDM interface should have started...

    IfxScuWdt_setCpuEndinit(IfxScuWdt_getCpuWatchdogPassword ());

}


