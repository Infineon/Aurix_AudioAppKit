# Simple Audio Loopback with Volume control

This example shows how to make a simple audio-loopback from the audio line-input to the headphone-output or to the amplifier.<br>
The audio-clock can be driven by the PLL (supporting sample-rates between 44.1 kHz to 96 kHz) or from the oscillator (sample-rate fixed at 48 kHz).<br>
This particular example uses the PLL at 44.1 kHz sample-rate.<br>
The loopback-volume can be controlled by the onboard potentiometer of the AURIX™ LiteKit. The user has to press the user-button during reset to activate the volume-control over potentiometer. Otherwise the volume is not manipulated.<br>
During runtime, the user-button can be used to activate/deactivate the Class-D amplifier.
<br><br><br>

## Needed Boards
* TC375 Lite Kit (KIT_A2G_TC375_LITE)
* Audio Shield Board (KIT_A2G_AUDIO_SHIELD)
<br><br><br>
## Usage
* Connect an audio-source to the audio line-input (LINE IN) e.g. a smartphone
* Connect a headphone to the headphone-output (HP OUT)
* In case the amplifier is used, connect an external power-supply to the Audio Shield (not to the barrel-jack of the Lite-Kit!)
<br><br><br>
## Jumper settings
* **ADC/MIC** -> set to ADC
* **3V3** -> Set to LK, alternatively if external power is applied, it can bet set to both
* **LK supply** -> Can be set to power the AURIX™ LiteKit in case an external power supply is connected.
<br><br><br>
<img src="/Documentation/Images/TC375_AUD_LB.jpg" width="600">  
