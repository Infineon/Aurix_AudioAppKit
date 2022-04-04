################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/AudioShield/Audio.c \
../Libraries/AudioShield/ExtControl.c 

OBJS += \
./Libraries/AudioShield/Audio.o \
./Libraries/AudioShield/ExtControl.o 

COMPILED_SRCS += \
./Libraries/AudioShield/Audio.src \
./Libraries/AudioShield/ExtControl.src 

C_DEPS += \
./Libraries/AudioShield/Audio.d \
./Libraries/AudioShield/ExtControl.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/AudioShield/%.src: ../Libraries/AudioShield/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fC:/Users/Noll/AudioKitProjects/Aurix_AudioAppKit/Examples/TC375 Lite Kit/MAB_ArrayMicrophoneLoopback_TC375/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/AudioShield/%.o: ./Libraries/AudioShield/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


