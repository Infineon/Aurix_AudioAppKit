################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/FreeRTOS/portable/TriCore/port.c 

OBJS += \
./Libraries/FreeRTOS/portable/TriCore/port.o 

COMPILED_SRCS += \
./Libraries/FreeRTOS/portable/TriCore/port.src 

C_DEPS += \
./Libraries/FreeRTOS/portable/TriCore/port.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/FreeRTOS/portable/TriCore/%.src: ../Libraries/FreeRTOS/portable/TriCore/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fC:/Users/Noll/AudioKitProjects/Aurix_AudioAppKit/Examples/TC375 Lite Kit/ASB_StereoMicrophoneLoopback_TC375/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O3 --tradeoff=0 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/FreeRTOS/portable/TriCore/%.o: ./Libraries/FreeRTOS/portable/TriCore/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


