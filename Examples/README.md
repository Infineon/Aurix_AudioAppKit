# AURIX™ Audio Code Examples

Here you can find a variety of code-examples for using the different Audio extension boards together with TC334/TC375 lite Kit.<br>
All code examples are based on FreeRTOS and provide by default also a UART handler to provide basic send/receive functionality as well as RTOS run time statistics.<br>
Some of the iLLD driver in the packages (especially for UART / I²C) were modified to make use of semaphores inside the FreeRTOS environment.
<br>
<br>
The example projects can be compiled and debugged with the [Aurix™ Development Studio](https://www.infineon.com/cms/en/product/promopages/aurix-development-studio/) (v1.5.2 upwards).<br>
As all projects in this repository are pre-compiled, the .hex files which can be found in the "Debug" folders can be also directly flashed to the boards using the [Infineon Memtool](https://www.infineon.com/cms/en/tools/aurix-tools/free-tools/infineon/).


