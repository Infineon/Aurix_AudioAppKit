# AURIX™ Audio Application Kit
Explore Audio processing on the AURIX™ platform


<img src="/Documentation/Images/ASB.jpg" height="200"> <img src="/Documentation/Images/MAB.jpg" height="200"> <img src="/Documentation/Images/a2b_system_top.PNG" height="200"> 


Refer also to the [Board manual](/Documentation/Board_Users_Manual_AURIX_Audio_AppKit_V1_0.pdf).


<br><br>
## Summary
The AURIX™ Audio AppKit consists of four different boards:

* Audio Shield Board
* Microphone Array Board
* A²B Master Interfacing Board
* A²B Slave Board
<br>

All four boards can be purchased separately dependent on the application use-case. <br>
The Audio Shield Board can be used stand-alone.<br>
**The Microphone Array Board can be only used in combination with the Audio Shield Board.**<br>
**The A²B Master Board must be used together with at least one A²B Slave Board**<br>
<br>

The AppKit was primarily designed to explore audio-functionalities on Aurix™ platform including
* Interfacing I²S / Left-Justified / TDM buses in Master-Mode
* Interfacing of PDM microphones in Stereo configuration and PDM decimation in software
* Synchronous interfacing of multiple PDM microphones in array configurations with PDM decimation in hardware
* Exploring different audio-clocking options including network-clock recovery for AVB applications
* Multipurpose Audio-Streaming over Ethernet
* Performance evaluation of XENSIV™ IM67D120A microphones and MERUS™ MA12070P amplifier
* Interfacing of A²B networks as A²B master-node



<br><br>
## Key Features and Benefits - Audio Shield Board
* Stereo XENSIV™ IM67D120A digital MEMS microphones with PDM interface
* MERUS™ MA12070P Stereo Multilevel Class-D Audio Amplifier
* SGTL5000 Audio-Codec with Line-Input, Headphone- and Line-Output
* CS2000CP Audio-PLL supporting various sample-rates and PTP audio-clock recovery (for e.g. AVB)
* Reverse Polarity Protection for power-input
* Reverse-Supply of the AURIX™ lite Kit V2
* Onboard OPTIREG™ voltage-regulators
  * TLS4120D0EPV
  * TLS205B0LD (V50 & V33)
  * TLS202A1MBV
<br><br><br>
<img src="/Documentation/Images/as_top_desc.PNG" width="600"> <br>
<img src="/Documentation/Images/as_bot_desc.PNG" width="600"> 

<br><br>
## Key Features and Benefits - Microphone Array Board
* Four XENSIV™ IM67D120A digital MEMS microphones with PDM interface as 2x2 array
* 12 LEDs in a 360° circle arrangement
* 3 generic status LEDs
<br><br><br>
<img src="/Documentation/Images/ms_top_desc.PNG" width="600"> <br>
<img src="/Documentation/Images/ms_bot_desc.PNG" width="600">  
  
 <br><br>
 ## Key Features and Benefits - A²B Master Board
 * AD2428W A²B Transceiver
 * ADAU1761 Audio Codec
 * Onboard OPTIREG™ TLS4120 voltage-regulator for A²B bus-power
<br><br><br>
<img src="/Documentation/Images/a2b_master_top.PNG" width="600"> 

<br><br>
 ## Key Features and Benefits - A²B Slave Board
 * AD2428W A²B Transceiver
 * Four XENSIV™ IM67D130A digital MEMS microphones with PDM interface as T array configuration 
<br><br><br>
<img src="/Documentation/Images/a2b_slave_top.PNG" width="600"> 

<br><br>
## Supported Microcontroller Boards
|   | Audio Shield Board | Microphone Array Board | A²B Master Board
| :---: | :---: | :---: | :---: |
| **AURIX™ TC375 lite Kit** | yes | yes | yes |
| **AURIX™ TC334 lite Kit** | yes | no | yes |


<br><br>
## Usage
Please follow the example projects in the /Examples directory to learn more about the usage of this AppKit.


<br><br>
## System-Concept & Board Documentation
In case you want to learn more about the I²S/PDM interfacing concepts or about the board-design, you can study the user-manual.

[AURIX™ Audio AppKit Documentation](/Documentation/Board_Users_Manual_AURIX_Audio_AppKit_V1_0.pdf)
