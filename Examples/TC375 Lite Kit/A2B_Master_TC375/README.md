# A²B Master Node with Audio Loopback

This example shows how to use the A²B master-board together with the microphone slave-nodes. The default configuration is 8-channel audio from two slave-boards (using all 4 microphones on each slave-node).<br>
Alternative configurations can be checked [here](/Examples/A2B_ConfigFiles).<br>
The example sums up all 8 received audio-channels to a stereo signal and loops it back to the headphone-output (HP OUT).
The loopback-volume can be controlled by the onboard potentiometer of the AURIX™ LiteKit. The user has to press the user-button during reset to activate the volume-control over potentiometer. Otherwise the volume is not manipulated.<br>
The system runs on a fixed 48 kHz sample-rate using a 8 channel TDM bus.<br><br>
Additionally, in comparison to the A2B example for TC334 LiteKit, the Microphone Array Board can be connected to the TC375 LiteKit making use of the LED's on the backside.
The 12 LEDs on the LED-circle are showing the realtime level of one single TDM channel (i.e. microphone) with level-steps of 3dB between each LED. The three information LEDs are showing in binary count (from 0-7) which channel is selected for level monitoring.
The user-button can be used during runtime to switch the level-metering between the different channels.


<br><br><br>

## Needed Boards
* TC375 Lite Kit (KIT_A2G_TC375_LITE)
* A²B Audio AppKit (EVAL_A2B_Kit-Full)
* Microphone Array Board (KIT_A2G_MIC_ARRAY)
<br><br><br>
## Usage
* Connect the A²B Master Board to the TC375 LiteKit
* Connect optinally the Microphone Array Board to the TC375 LiteKit
* Connect a headphone to the headphone-output (HP OUT)
* Connect two A²B Slave Boards to the A²B Master Board with the A²B cables
* Provide a 12V power-supply connected to the A²B Master Board (not to the barrel-jack of the Lite-Kit!)


