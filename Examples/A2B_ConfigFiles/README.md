# A²B Configuration Files

Here you can find a variety of configuration files for the A²B network. <br>
In the example-projects, the 2x Slave-Board configuration is used by default. <br>
The configuration can be changed by copy&paste the content of those header-files into the "ADI_DEV_CFG.h" file which can be found in the "Configurations" folder inside the sample projects.<br>
The TDM-Bus between Aurix and A²B Transceiver will always run in 8-channel mode. However, in the 4-channel configuration, only 4 out of 8 slots of the TDM are used.
<br><br>
Following configurations are available:
<br>

* 8 Channel Audio - 2x A²B Slave-Boards using 4 Microphones each (IFX_a2b_aurix_TDM_2nodes_i2c_commandlist.h)
* 8 Channel Audio - 4x A²B Slave-Boards using 2 Microphones each (IFX_a2b_aurix_TDM_4nodes_i2c_commandlist.h)
* 4 Channel Audio - 1x A²B Slave-Board using 4 Microphones (IFX_a2b_aurix_TDM_1nodes_i2c_commandlist.h)
