################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AudioTask.c \
../Cpu0_Main.c \
../Cpu1_Main.c \
../Cpu2_Main.c \
../UartTask.c 

OBJS += \
./AudioTask.o \
./Cpu0_Main.o \
./Cpu1_Main.o \
./Cpu2_Main.o \
./UartTask.o 

COMPILED_SRCS += \
./AudioTask.src \
./Cpu0_Main.src \
./Cpu1_Main.src \
./Cpu2_Main.src \
./UartTask.src 

C_DEPS += \
./AudioTask.d \
./Cpu0_Main.d \
./Cpu1_Main.d \
./Cpu2_Main.d \
./UartTask.d 


# Each subdirectory must supply rules for building sources it contributes
%.src: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fC:/Users/Noll/AudioKitProjects/Aurix_AudioAppKit/Examples/TC375 Lite Kit/A2B_Master_TC375/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

%.o: ./%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


