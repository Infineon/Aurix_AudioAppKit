# Stereo-PDM microphone with Volume control

This examples shows how to use the two IM67D120A microphones on the Audio Shield Board in Stereo-PDM configuration and loops the sound back to the headphone-output / amplifier. <br>
In this example, the sample-rate is fixed to 48 kHz by using the oscillator (PLL not used). The sound of the microphones can be checked by connecting a headphone to the headphone-output. One microphone is on the right channel and the other microphone is on the left channel. <br>
The loopback-volume can be controlled by the onboard potentiometer of the AURIX™ LiteKit. The user has to press the user-button during reset to activate the volume-control over potentiometer. Otherwise the volume is not manipulated.<br>
During runtime, the user-button can be used to activate/deactivate the Class-D amplifier. Please be aware that a loudspeaker in the near of the microphone can lead to feedback.
<br><br><br>

## Needed Boards
* TC375 Lite Kit (KIT_A2G_TC375_LITE)
* Audio Shield Board (KIT_A2G_AUDIO_SHIELD)
<br><br><br>
## Usage
* Connect a headphone to the headphone-output (HP OUT)
* In case the amplifier is used, connect an external power-supply to the Audio Shield (not to the barrel-jack of the Lite-Kit!)
<br><br><br>
## Jumper settings
* **ADC/MIC** -> set to MIC
* **3V3** -> Set to LK, alternatively if external power is applied, it can bet set to both
* **LK supply** -> Can be set to power the **Aurix<sup>TM</sup> lite Kit V2** in case an external power supply is connected.
<br><br><br>
<img src="/Documentation/Images/TC375_MIC_LB.jpg" width="600">  
