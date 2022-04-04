################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/FreeRTOS/portable/MemMang/heap_4.c 

OBJS += \
./Libraries/FreeRTOS/portable/MemMang/heap_4.o 

COMPILED_SRCS += \
./Libraries/FreeRTOS/portable/MemMang/heap_4.src 

C_DEPS += \
./Libraries/FreeRTOS/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/FreeRTOS/portable/MemMang/%.src: ../Libraries/FreeRTOS/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc33x "-fC:/Users/Noll/AudioKitProjects/Aurix_AudioAppKit/Examples/TC334 Lite Kit/ASB_StereoMicrophoneLoopback_TC334/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc33x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/FreeRTOS/portable/MemMang/%.o: ./Libraries/FreeRTOS/portable/MemMang/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


