# A²B Master Node with Audio Loopback

This example shows how to use the A²B master-board together with the microphone slave-nodes. The default configuration is 8-channel audio from two slave-boards (using all 4 microphones on each slave-node).<br>
Alternative configurations can be checked [here](/Examples/A2B_ConfigFiles).<br>
The example sums up all 8 received audio-channels to a stereo signal and loops it back to the headphone-output (HP OUT).
The loopback-volume can be controlled by the onboard potentiometer of the AURIX™ LiteKit. The user has to press the user-button during reset to activate the volume-control over potentiometer. Otherwise the volume is not manipulated.<br>
During runtime, the user-button can be used to switch the audio source to the line-input on the board (instead using the microphones).<br>
The system runs on a fixed 48 kHz sample-rate using a 8 channel TDM bus.


<br><br><br>

## Needed Boards
* TC334 Lite Kit (KIT_A2G_TC334_LITE)
* A²B Audio AppKit (EVAL_A2B_Kit-Full)

<br><br><br>
## Usage
* Connect the A²B Master Board to the TC334 LiteKit
* Connect a headphone to the headphone-output (HP OUT)
* Connect two A²B Slave Boards to the A²B Master Board with the A²B cables
* Provide a 12V power-supply connected to the A²B Master Board (not to the barrel-jack of the Lite-Kit!)
<br><br><br>
<img src="/Documentation/Images/TC334_A2B_LB.jpg" width="600">  

