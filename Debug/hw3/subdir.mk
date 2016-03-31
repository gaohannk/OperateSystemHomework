################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hw3/q1.c \
../hw3/q2.c \
../hw3/q3.c 

OBJS += \
./hw3/q1.o \
./hw3/q2.o \
./hw3/q3.o 

C_DEPS += \
./hw3/q1.d \
./hw3/q2.d \
./hw3/q3.d 


# Each subdirectory must supply rules for building sources it contributes
hw3/%.o: ../hw3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


