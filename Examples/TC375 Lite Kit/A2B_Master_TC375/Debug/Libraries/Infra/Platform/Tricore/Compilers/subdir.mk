################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Infra/Platform/Tricore/Compilers/CompilerDcc.c \
../Libraries/Infra/Platform/Tricore/Compilers/CompilerGhs.c \
../Libraries/Infra/Platform/Tricore/Compilers/CompilerGnuc.c \
../Libraries/Infra/Platform/Tricore/Compilers/CompilerTasking.c 

OBJS += \
./Libraries/Infra/Platform/Tricore/Compilers/CompilerDcc.o \
./Libraries/Infra/Platform/Tricore/Compilers/CompilerGhs.o \
./Libraries/Infra/Platform/Tricore/Compilers/CompilerGnuc.o \
./Libraries/Infra/Platform/Tricore/Compilers/CompilerTasking.o 

COMPILED_SRCS += \
./Libraries/Infra/Platform/Tricore/Compilers/CompilerDcc.src \
./Libraries/Infra/Platform/Tricore/Compilers/CompilerGhs.src \
./Libraries/Infra/Platform/Tricore/Compilers/CompilerGnuc.src \
./Libraries/Infra/Platform/Tricore/Compilers/CompilerTasking.src 

C_DEPS += \
./Libraries/Infra/Platform/Tricore/Compilers/CompilerDcc.d \
./Libraries/Infra/Platform/Tricore/Compilers/CompilerGhs.d \
./Libraries/Infra/Platform/Tricore/Compilers/CompilerGnuc.d \
./Libraries/Infra/Platform/Tricore/Compilers/CompilerTasking.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Infra/Platform/Tricore/Compilers/%.src: ../Libraries/Infra/Platform/Tricore/Compilers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fC:/Users/Noll/AudioKitProjects/Aurix_AudioAppKit/Examples/TC375 Lite Kit/A2B_Master_TC375/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/Infra/Platform/Tricore/Compilers/%.o: ./Libraries/Infra/Platform/Tricore/Compilers/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


