################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/FreeRTOS/croutine.c \
../Libraries/FreeRTOS/event_groups.c \
../Libraries/FreeRTOS/list.c \
../Libraries/FreeRTOS/queue.c \
../Libraries/FreeRTOS/stream_buffer.c \
../Libraries/FreeRTOS/tasks.c \
../Libraries/FreeRTOS/timers.c 

OBJS += \
./Libraries/FreeRTOS/croutine.o \
./Libraries/FreeRTOS/event_groups.o \
./Libraries/FreeRTOS/list.o \
./Libraries/FreeRTOS/queue.o \
./Libraries/FreeRTOS/stream_buffer.o \
./Libraries/FreeRTOS/tasks.o \
./Libraries/FreeRTOS/timers.o 

COMPILED_SRCS += \
./Libraries/FreeRTOS/croutine.src \
./Libraries/FreeRTOS/event_groups.src \
./Libraries/FreeRTOS/list.src \
./Libraries/FreeRTOS/queue.src \
./Libraries/FreeRTOS/stream_buffer.src \
./Libraries/FreeRTOS/tasks.src \
./Libraries/FreeRTOS/timers.src 

C_DEPS += \
./Libraries/FreeRTOS/croutine.d \
./Libraries/FreeRTOS/event_groups.d \
./Libraries/FreeRTOS/list.d \
./Libraries/FreeRTOS/queue.d \
./Libraries/FreeRTOS/stream_buffer.d \
./Libraries/FreeRTOS/tasks.d \
./Libraries/FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/FreeRTOS/%.src: ../Libraries/FreeRTOS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fC:/Users/Noll/AudioKitProjects/Aurix_AudioAppKit/Examples/TC375 Lite Kit/A2B_Master_TC375/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/FreeRTOS/%.o: ./Libraries/FreeRTOS/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


