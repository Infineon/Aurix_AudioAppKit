################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.asm.c \
../iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.c \
../iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_Fifo.c 

OBJS += \
./iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.asm.o \
./iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.o \
./iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_Fifo.o 

COMPILED_SRCS += \
./iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.asm.src \
./iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.src \
./iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_Fifo.src 

C_DEPS += \
./iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.asm.d \
./iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.d \
./iLLD/TC37A/Tricore/_Lib/DataHandling/Ifx_Fifo.d 


# Each subdirectory must supply rules for building sources it contributes
iLLD/TC37A/Tricore/_Lib/DataHandling/%.src: ../iLLD/TC37A/Tricore/_Lib/DataHandling/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fC:/Users/Noll/AudioKitProjects/Aurix_AudioAppKit/Examples/TC375 Lite Kit/ASB_StereoMicrophoneLoopback/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O3 --tradeoff=0 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

iLLD/TC37A/Tricore/_Lib/DataHandling/%.o: ./iLLD/TC37A/Tricore/_Lib/DataHandling/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


