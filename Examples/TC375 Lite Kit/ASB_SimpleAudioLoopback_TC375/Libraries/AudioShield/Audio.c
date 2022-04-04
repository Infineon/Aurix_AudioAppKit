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
#include <I2c/I2c/IfxI2c_I2c.h>
#include <stdint.h>
#include "IfxStm.h"
/*****************************************************************************/
/*-----------------------------------Macros----------------------------------*/
/*****************************************************************************/

/*****************************************************************************/
/*------------------------------Global variables-----------------------------*/
/*****************************************************************************/

static IfxI2c_I2c i2c;
static IfxI2c_I2c_Device i2c_Codec, i2c_PLL;

//PLL multiplier value
uint32_t mult = 0;


//Audio RX/TX Buffer
int32_t __attribute__ ((__align(4*128))) rxBuf[128];
int32_t __attribute__ ((__align(4*128))) txBuf[128];

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
 * Inits the I²C peripheral for communication to PLL / Codec
 */

void I2CInit(void) {
    // create config structure
    IfxI2c_I2c_Config config;

    // fill structure with default values and Module address
    IfxI2c_I2c_initConfig(&config, &MODULE_I2C0);

    // configure pins
    const IfxI2c_Pins pins = {
        &IfxI2c0_SCL_P13_1_INOUT,
        &IfxI2c0_SDA_P13_2_INOUT,
        IfxPort_PadDriver_ttlSpeed1
    };

    config.pins = &pins;

    //Configure Baudrate
    config.mode = IfxI2c_Mode_HighSpeed;
    config.baudrate = 200000;

    // initialize module
    IfxI2c_I2c_initModule(&i2c, &config);

    // create device config
    IfxI2c_I2c_deviceConfig i2cDeviceConfigCodec;
    IfxI2c_I2c_deviceConfig i2cDeviceConfigPLL;

    // fill structure with default values and i2c Handler
    IfxI2c_I2c_initDeviceConfig(&i2cDeviceConfigCodec, &i2c);
    IfxI2c_I2c_initDeviceConfig(&i2cDeviceConfigPLL, &i2c);

    // set device specifig values.
    i2cDeviceConfigCodec.deviceAddress = 0x0a<<1;  // 8 bit device address
    i2cDeviceConfigPLL.deviceAddress = 0x4e<<1;  // 8 bit device address

    // initialize the i2c device handle
    IfxI2c_I2c_initDevice(&i2c_Codec, &i2cDeviceConfigCodec);
    IfxI2c_I2c_initDevice(&i2c_PLL, &i2cDeviceConfigPLL);

}

/*
 * Function to write register to Cirrus Logic CS2x00CP PLL
 */
void I2CWriteCS2x00(uint8_t address, uint8_t data) {
    uint8_t txbuf[4];
    uint8_t size=2;
    txbuf[0] = address;
    txbuf[1] = data;
    while(IfxI2c_I2c_write(&i2c_PLL, txbuf, size) == IfxI2c_I2c_Status_nak);
}

/*
 * Function to read register to Cirrus Logic CS2x00CP PLL
 */
void I2CReadCS2x00(uint8_t address, uint8_t *data) {
    uint8_t datarx;

    while(IfxI2c_I2c_write(&i2c_PLL, &address, 1) == IfxI2c_I2c_Status_nak);
    while(IfxI2c_I2c_read(&i2c_PLL, &datarx, 1) == IfxI2c_I2c_Status_nak);
    *data = datarx;
}


/*
 * Function to write register to NXP SGTL5000 Codec
 */
void I2CWriteSGTL5000(uint16_t address, uint16_t data) {

    uint8_t txbuf[4];
    uint8_t size=4;
    txbuf[0] = (address>>8)&0xff;
    txbuf[1] = address&0xff;
    txbuf[2] = (data>>8)&0xff;
    txbuf[3] = data&0xff;
    while(IfxI2c_I2c_write(&i2c_Codec, txbuf, size) == IfxI2c_I2c_Status_nak);
}


/*
 * Initializes the MA12070P amplifier and SGTL5000 Codec
 * Used I²S Format: Left-Justified, 2*32 Bit Framing (BCLK=64*fs), MCLK=256*fs
 */
void InitAmpAndCodec(void) {

    //Before Calling this function, make sure, that all audio-clocks are supplied and stable


    //Init Amplifier

    //For standard I²S-LeftJustified operation with 32-Bit Framing, no additional configuration must be loaded over I²C into MA120x0p series amplifier
    //Therefore, only the Amp-Disable and Amp-Mute pins are used to control the amp
    //Amp-Disable = P15.3
    //Amp-Unmute = P15.2

    //Set P15.3 + P15.2 as GPIO OUTPUT
    P15_IOCR0.B.PC3 = 0x10;
    P15_IOCR0.B.PC2 = 0x10;

    //Set amp to enable (amp-enable -> low active) and Mute (Unmute-Pin -> high active)
    P15_OUT.B.P3 = 0;
    P15_OUT.B.P2 = 0;




    //Init SGTL5000 Audio Codec
    //This routine inits the codec to be used as standard ADC/DAC operation (without using the internal's DSP features)
    //Line-Input is routed to it's i²s-out and and i²s-input is routed to headphone and line-output
    //Format is I²S-LeftJustified, 32-Bit framing (SCLK = 64*fs) and MCLK = 256*fs

    //Register: CHIP_ANA_POWER
    //VDDD is externally driven with 1.8V
    I2CWriteSGTL5000(0x0030, 0x4060);

    //Register: CHIP_LINEREG_CTRL
    //VDDA & VDDIO both over 3.1V
    I2CWriteSGTL5000(0x0026, 0x006C);

    //Register: CHIP_REF_CTRL
    //VAG=1.575, normal ramp, +12.5% bias current
    I2CWriteSGTL5000(0x0028, 0x01F2);

    //Register: CHIP_LINE_OUT_CTRL
    //LO_VAGCNTRL=1.65V, OUT_CURRENT=0.54mA
    I2CWriteSGTL5000(0x002c, 0x0F22);

    //Register: CHIP_SHORT_CTRL
    //allow headphone current up to 125mA
    I2CWriteSGTL5000(0x003c, 0x4446);

    //Register: CHIP_ANA_CTRL
    //ADC-Input = Line-IN
    //Mute ADC
    //Mute Headpgone output
    //Lineout Mute
    //Enable zero-cross detectors
    I2CWriteSGTL5000(0x0024, 0x0137);

    //Register: CHIP_ANA_POWER
    // power up: lineout, hp, adc, dac
    I2CWriteSGTL5000(0x0030, 0x40FF);

    //Register: CHIP_DIG_POWER
    //power up all digital stuff
    I2CWriteSGTL5000(0x0002, 0x0073);

    //Register: CHIP_LINE_OUT_VOL
    //default approx 1.3 volts peak-to-peak
    I2CWriteSGTL5000(0x002e, 0x1D1D);

    //Register: CHIP_CLK_CTRL
    //MCLK frequency is 256*fs
    I2CWriteSGTL5000(0x0004, 0x0008);

    //Register: CHIP_I2S_CTRL
    //SCLK is 64*fs
    //Left-Justified Format! (no standard I²S format)
    I2CWriteSGTL5000(0x0006, 0x0002);

    //Register: CHIP_SSS_CTRL
    //ADC to I²S DOUT
    //DAC from I²S DIN
    I2CWriteSGTL5000(0x000a, 0x0010);

    //Register: CHIP_ADCDAC_CTRL
    //Disable DAC mute
    I2CWriteSGTL5000(0x000e, 0x0000);

    //Register: CHIP_DAC_VOL
    //Digital Gain to 0dB
    I2CWriteSGTL5000(0x0010, 0x3C3C);

    //Register: CHIP_ANA_HP_CTRL
    //Set volume to 0dB
    I2CWriteSGTL5000(0x0022, 0x1F1F);

    //Register CHIP_ANA_CTRL
    //ADC Input is Line_IN
    //Unmute Headphone
    I2CWriteSGTL5000(0x0024, 0x0026);


}


/*
 * Initializes the CS2x00 PLL in fixed frequency synthesizer mode (standalone mode)
 * In 48 kHz sample-rate mode, the PLL will generate a 24.576 MHz reference-clock
 * In 44.1 kHz sample-rate mode, the PLL will generate a 22.5792 MHz reference-clock
 * In 96 kHz sample-rate mode, the PLL will generate a 49.152 MHz reference-clock
 * In 88.2 kHz sample-rate mode, the PLL will generate a 45.1584 MHz reference-clock
 */
void InitCS2x00(uint32_t samplerate) {

    //PLL lock signal is connected to P40.9/AN39
    //As this pin is by default an analog-input pin, it must be switched to digital functionality

    IfxScuWdt_clearCpuEndinit(IfxScuWdt_getCpuWatchdogPassword ());
    P40_PDISC.B.PDIS9 = 0;
    IfxScuWdt_setCpuEndinit(IfxScuWdt_getCpuWatchdogPassword ());


    //the datasheet of CS2x00 PLL states that all reserved bits must be kept as they are
    //-> therefore, every register is being read in advance and manipualted afterwards



    uint8_t readback;

    //Register: Device Configuration 1
    //R-Mod -> No Shift
    //AuxOut -> set as PLL lock indicator
    //Enable device configuration
    I2CReadCS2x00(0x03, &readback);
    readback &= 0x18;
    readback |= 0x07;
    I2CWriteCS2x00(0x03, readback);

    //Register: Global Configuration
    //Enable device freeze
    //enable second device configuration bit
    I2CReadCS2x00(0x05, &readback);
    readback &= 0xF6;
    readback |= 0x09;
    I2CWriteCS2x00(0x05, readback);

    //Register: Function Configuration 2
    //enable clock output always
    //Enable fractional high-accuracy mode
    I2CReadCS2x00(0x17, &readback);
    readback &= 0xE7;
    readback |= 0x18;
    I2CWriteCS2x00(0x17, readback);

    //Register: Function Configuration 1
    //clock-skip disabled (as PLL is used in standalone mode)
    //Set reference-clock divider to /2 -> as reference-oscillator is in range between 16MHz and 28 MHz (=24.576 MHz)
    I2CReadCS2x00(0x16, &readback);
    readback &= 0x27;
    readback |= 0x08;
    I2CWriteCS2x00(0x16, readback);


    //Register: Device Configuration 1
    //PLL used in static frequency synthesizer mode (standalone mode)
    //Ratio 0 register selected
    I2CReadCS2x00(0x04, &readback);
    readback &= 0xF8;
    readback |= 0x00;
    I2CWriteCS2x00(0x04, readback);





    //Registers: Ratio0 configuration register (0x06 to 0x09)

    //External reference oscillator is 24.576 MHz

    //For 48 kHz sample-rate, a ref-clock of 24.576 MHz is needed, therefore the ratio multiplier is 1.0 => 1.0*(2^20) = 1048576
    //For 44.1 kHz sample-rate a ref-clock of 22.5792 MHz is needed, therefore the ratio multiplier is 0.91875 => 0.91875*(2^20) = 963379
    //For 88.2 khz and 96 kHz above factors are multiplied by 2x
    //use 48 kHz as default

    if (samplerate == 44100) mult = 963379;
    else if (samplerate == 88200) mult = 963379*2;
    else if (samplerate == 96000) mult = 1048576*2;
    else mult = 1048576; //backup use 48 kHz

    readback = (mult>>24)&0xFF;
    I2CWriteCS2x00(0x06, readback);
    readback = (mult>>16)&0xFF;
    I2CWriteCS2x00(0x07, readback);
    readback = (mult>>8)&0xFF;
    I2CWriteCS2x00(0x08, readback);
    readback = (mult)&0xFF;
    I2CWriteCS2x00(0x09, readback);

    //Register: Device Control
    //enable aux-output
    I2CReadCS2x00(0x02, &readback);
    readback &= 0x7C;
    readback |= 0x00;
    I2CWriteCS2x00(0x02, readback);

    //Register: Global Configuration
    //Set Freeze-Bit to 0 to take effect of new ratio configured
    //disable device configuration
    I2CReadCS2x00(0x05, &readback);
    readback &= 0xF6;
    readback |= 0x01;
    I2CWriteCS2x00(0x05, readback);


}

/*
 * This function can be used to make a small positive/negative offset to the configured base reference-clock (e.g. for synchronizing the local audio-clock to an incoming audio-stream over e.g. ethernet)
 * Warning: This function is experimental
 */

void SetCS2x00Offset(int16_t val) {
    uint8_t readback;

    I2CReadCS2x00(0x03, &readback);
    readback &= 0x18;
    readback |= 0x07;
    I2CWriteCS2x00(0x03, readback);

    I2CReadCS2x00(0x05, &readback);
    readback &= 0xF6;
    readback |= 0x09;
    I2CWriteCS2x00(0x05, readback);


    mult += val;

    readback = (mult>>24)&0xFF;
    I2CWriteCS2x00(0x06, readback);
    readback = (mult>>16)&0xFF;
    I2CWriteCS2x00(0x07, readback);
    readback = (mult>>8)&0xFF;
    I2CWriteCS2x00(0x08, readback);
    readback = (mult)&0xFF;
    I2CWriteCS2x00(0x09, readback);

    I2CReadCS2x00(0x05, &readback);
    readback &= 0xF6;
    readback |= 0x01;
    I2CWriteCS2x00(0x05, readback);


}


/*
 * This function unmutes the MA12070P amplifier
 */
void UnmuteAmp(void) {
    P15_OUT.B.P2 = 1;
}


/*
 * This function mutes the MA12070P amplifier
 */
void MuteAmp(void) {
    P15_OUT.B.P2 = 0;
}


/*
 * Initializes the Ref-Clock mux to select between directly from 24.576 MHz reference-oscillator (usable only for 48 kHz operation) or from CS2x00 PLL
 */
void InitRefClockMux(uint8_t val) {

    //Ref-Clock mux is connected to P10.5

    //Set P10.5 as GPIO output
    P10_IOCR4.B.PC5 = 0x10;

    //if val==0 -> OSC is selected
    //if val==1 -> PLL is selected
    P10_OUT.B.P5 = val;

}

/*
 * This function can check if external CS2x00 PLL has locked
 * Return 1 -> PLL is locked
 * Return 0 -> PLL is unlocked
 */
uint8_t IsPllLock(void) {
    if (P40_IN.B.P9==0) return 1;
    return 0;
}


/*
 * This function initializes the I²S emulation based on QSPI/GTM. Data I/O is operated by DMA in double-buffering mode.
 * The RX/TX buffer sizes are fixed to 2*64 words buffer (32-Bit)
 */
void I2S_Init_DMA(void) {




    /*
     * inits the GTM together with QSPI (Slave-Mode) to make a I2S master-interface.
     *
     * P2.4 -> QSPI3_SLSIA -> QSPI sync input
     * P2.5 -> QSPI3_MRST -> QSPI Slave data output (I2S data out)
     * P2.6 -> QSPI3_MTSRA -> QSPI Slave data input (I2S data in)
     * P2.7 -> QSPI_SCLKA -> QSPI Slave clock input (negative phase BCLK)
     *
     *
     * Hint: Mentioned frequencies below are only as example for 48 kHz mode
     *
     * P2.0 -> GTM_TIM0CH0 -> 24.576 MHz reference clock input (from Oscillator or PLL)
     * P2.1 -> GTM_TOUT1 / TOM0CH9 -> 12.288 MHz I2S MCLK output
     * P2.3 -> GTM_TOUT3 / TOM0CH11 -> QSPI-Sync output -> for syncing qspi module to i2s clocking
     * P10.1 -> GTM_TOUT103 / TOM0CH1 -> 3.072 MHz I2S BCLK output
     * P10.2 -> GTM_TOUT104 / TOM0CH2 -> 3.072 MHz I2S Inverted BCLK output (for clocking QSPI module)
     * P10.3 -> GTM_TOUT105 / TOM0CH3 -> 48kHz LRCLK output
     *
     *
     *
     * QSPI_SCKLA must be directly connected to Inverted BCLK output (P10.2 -> P2.7)
     * QSPI_SLSIA must be connected with QSPI-sync output (P2.3 -> P2.4)
     *
     * I2S Format = 64 cycles per WCLK cycle = 2*32 bit framing
     * I2S MCLK output -> P2.1  -> 12.288 MHz
     * I2S BCLK output -> P10.1 -> 3.072 MHz
     * I2S WCLK output -> P10.3 -> 48 kHz
     * I2S data in (from external ADC) P2.6
     * I2S data out (to external DAC) P2.5
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
    DMA_SHADR050.U          = (uint32) &rxBuf[64]; //address of second buffer half
    DMA_ADICR050.B.DMF      = 0; /* Destination address modified by 1x CHDW */
    DMA_ADICR050.B.INCD     = 1; /* Increment destination address automatically */
    DMA_ADICR050.B.DCBE     = 1; /* Enable destination circular buffer */
    DMA_ADICR050.B.WRPDE    = 1; /* Enable wrap destination buffer interrupt */
    DMA_ADICR050.B.CBLD     = 8; /* 64 (32-bit) words per single buffer */

    DMA_ADICR050.B.STAMP    = 0; /* Disable timestamp */


    DMA_CHCFGR050.B.TREL    = 64; /* Transfer count reload value: 64 words per buffer */
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
    DMA_SHADR049.U          = (uint32) &txBuf[64];

    //define tx dma destination
    DMA_DADR049.U           = (uint32) &QSPI3_DATAENTRY0.U;
    DMA_ADICR049.B.DCBE     = 1; /* Enable destination circular buffer */
    DMA_ADICR049.B.CBLD     = 0; /* circular buffer length destination is 0 - always same address */
    DMA_ADICR049.B.WRPDE    = 0; /* Disable wrap destination buffer interrupt */

    DMA_ADICR049.B.SMF      = 0; /* source address modified by 1x CHDW */
    DMA_ADICR049.B.INCS     = 1; /* Increment source address automatically */
    DMA_ADICR049.B.SCBE     = 1; /* Enable source circular buffer */
    DMA_ADICR049.B.WRPSE    = 1; /* Enable wrap source buffer interrupt */
    DMA_ADICR049.B.CBLS     = 8; /* 64 (32-bit) words per single buffer */

    DMA_ADICR049.B.STAMP    = 0;  /* Disable timestamp */

    DMA_CHCFGR049.B.TREL    = 64; /* Transfer count reload value: 64 words per buffer */
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
     * Configure TOM0CH1 which is BCLK (normal phase) -> divide CLKINPUT/8 -> 24.576/8 = 3.072 MHz
     * Clocking derived from TRIG_(x) chain
     */
    GTM_TOM0_CH1_CN0.U = 0;
    GTM_TOM0_CH1_SR0.U = 8;
    GTM_TOM0_CH1_SR1.U = 4;
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
     * Configure TOM0CH2 which is BCLK inverted -> divide CLKINPUT/8 -> 24.576/8 = 3.072 MHz with offset of 4 = 180° shift
     * Clocking derived from TRIG_(x) chain
     */
    GTM_TOM0_CH2_CN0.U = 4;
    GTM_TOM0_CH2_SR0.U = 8;
    GTM_TOM0_CH2_SR1.U = 4;
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
    GTM_TOM0_CH3_CN0.U = 4;
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
    GTM_TOM0_CH9_CN0.U = 1;
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
     * This TOM is configured as one-shot (single high-to-low transition) to synchronize to QSPI module to the I2S clocking.
     * The one-shot high-time must be carefully chose to exactly align with a falling I2S-WCLK-edge (for left-justified operation)
     * For standard i2s format, this value must be set to match for example with the next falling I2S-BCLK-edge after WCLK high-to-low transition
     */
    uint16 slsival = 512+256-4; //wait one+half (1.5) wclk cycles to start shifting in low-phase of wclk (left channel); -4 (minus 4) as wclk<->bclk phase offset is 4 (refclk) cycles
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






     //now the I2S interface should have started...

    IfxScuWdt_setCpuEndinit(IfxScuWdt_getCpuWatchdogPassword ());

}


