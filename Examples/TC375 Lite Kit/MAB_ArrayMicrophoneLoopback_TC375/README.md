# Microphone Array Board with volume control

This examples shows how to use the 4 microphones of the Microphone Array Board, demodulating the PDM streams by using the EDSADC peripherals and loops the sound back to the headphone-output / amplifier.<br>
The sample-rate is fixed to 48 kHz by using the oscillator (PLL not used). The sound of the microphones can be checked by connecting a headphone to the headphone-output. 
Two microphones are on the headphone's left channel and the other two microphones are on the headphone's right channel.<br>
The three Info-LEDs and the LED circle are blinking in parallel.<br>
The loopback-volume can be controlled by the onboard potentiometer of the AURIX™ LiteKit. The user has to press the user-button during reset to activate the volume-control over potentiometer. Otherwise the volume is not manipulated.<br>
During runtime, the user-button can be used to activate/deactivate the Class-D amplifier. Please be aware that a loudspeaker in the near of the microphone can lead to feedback.

## Needed Boards
* TC375 Lite Kit (KIT_A2G_TC375_LITE)
* Audio Shield Board (KIT_A2G_AUDIO_SHIELD)
* Microphone Array Board (KIT_A2G_MIC_ARRAY)
<br /><br /><br />
## Usage
* Connect a headphone to the headphone-output (HP OUT)
* In case the amplifier is used, connect an external power-supply to the Audio Shield (not to the barrel-jack of the Lite-Kit!)
<br /><br /><br />
## Jumper settings
* **ADC/MIC** -> not used / doesn't care
* **3V3** -> Set to LK, alternatively if external power is applied, it can bet set to both
* **LK supply** -> Can be set to power the AURIX™ LiteKit in case an external power supply is connected.