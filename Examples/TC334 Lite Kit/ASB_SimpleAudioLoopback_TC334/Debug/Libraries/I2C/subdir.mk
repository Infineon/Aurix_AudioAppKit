################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/I2C/i2c0.c 

OBJS += \
./Libraries/I2C/i2c0.o 

COMPILED_SRCS += \
./Libraries/I2C/i2c0.src 

C_DEPS += \
./Libraries/I2C/i2c0.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/I2C/%.src: ../Libraries/I2C/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc33x "-fC:/Users/Noll/AudioKitProjects/Aurix_AudioAppKit/Examples/TC334 Lite Kit/ASB_SimpleAudioLoopback_TC334/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc33x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/I2C/%.o: ./Libraries/I2C/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


