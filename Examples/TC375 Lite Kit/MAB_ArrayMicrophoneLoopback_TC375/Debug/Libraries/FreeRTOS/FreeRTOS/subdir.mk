################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/FreeRTOS/FreeRTOS/croutine.c \
../Libraries/FreeRTOS/FreeRTOS/event_groups.c \
../Libraries/FreeRTOS/FreeRTOS/list.c \
../Libraries/FreeRTOS/FreeRTOS/queue.c \
../Libraries/FreeRTOS/FreeRTOS/stream_buffer.c \
../Libraries/FreeRTOS/FreeRTOS/tasks.c \
../Libraries/FreeRTOS/FreeRTOS/timers.c 

OBJS += \
./Libraries/FreeRTOS/FreeRTOS/croutine.o \
./Libraries/FreeRTOS/FreeRTOS/event_groups.o \
./Libraries/FreeRTOS/FreeRTOS/list.o \
./Libraries/FreeRTOS/FreeRTOS/queue.o \
./Libraries/FreeRTOS/FreeRTOS/stream_buffer.o \
./Libraries/FreeRTOS/FreeRTOS/tasks.o \
./Libraries/FreeRTOS/FreeRTOS/timers.o 

COMPILED_SRCS += \
./Libraries/FreeRTOS/FreeRTOS/croutine.src \
./Libraries/FreeRTOS/FreeRTOS/event_groups.src \
./Libraries/FreeRTOS/FreeRTOS/list.src \
./Libraries/FreeRTOS/FreeRTOS/queue.src \
./Libraries/FreeRTOS/FreeRTOS/stream_buffer.src \
./Libraries/FreeRTOS/FreeRTOS/tasks.src \
./Libraries/FreeRTOS/FreeRTOS/timers.src 

C_DEPS += \
./Libraries/FreeRTOS/FreeRTOS/croutine.d \
./Libraries/FreeRTOS/FreeRTOS/event_groups.d \
./Libraries/FreeRTOS/FreeRTOS/list.d \
./Libraries/FreeRTOS/FreeRTOS/queue.d \
./Libraries/FreeRTOS/FreeRTOS/stream_buffer.d \
./Libraries/FreeRTOS/FreeRTOS/tasks.d \
./Libraries/FreeRTOS/FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/FreeRTOS/FreeRTOS/%.src: ../Libraries/FreeRTOS/FreeRTOS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fC:/Users/Noll/AudioKitProjects/Aurix_AudioAppKit/Examples/TC375 Lite Kit/MAB_ArrayMicrophoneLoopback_TC375/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/FreeRTOS/FreeRTOS/%.o: ./Libraries/FreeRTOS/FreeRTOS/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


