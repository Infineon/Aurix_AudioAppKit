################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.asm.c \
../Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.c \
../Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_Fifo.c 

OBJS += \
./Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.asm.o \
./Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.o \
./Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_Fifo.o 

COMPILED_SRCS += \
./Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.asm.src \
./Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.src \
./Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_Fifo.src 

C_DEPS += \
./Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.asm.d \
./Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.d \
./Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_Fifo.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling/%.src: ../Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fC:/Users/Noll/AudioKitProjects/Aurix_AudioAppKit/Examples/TC375 Lite Kit/A2B_Master_TC375/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling/%.o: ./Libraries/iLLD/TC37A/Tricore/_Lib/DataHandling/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '

