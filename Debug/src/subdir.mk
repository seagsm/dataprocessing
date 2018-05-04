################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/data_line_parcer.c \
../src/data_processing.c \
../src/data_utilites.c 

OBJS += \
./src/data_line_parcer.o \
./src/data_processing.o \
./src/data_utilites.o 

C_DEPS += \
./src/data_line_parcer.d \
./src/data_processing.d \
./src/data_utilites.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


