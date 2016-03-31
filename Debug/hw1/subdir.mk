################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hw1/q1.c \
../hw1/q2.c \
../hw1/q3.c 

OBJS += \
./hw1/q1.o \
./hw1/q2.o \
./hw1/q3.o 

C_DEPS += \
./hw1/q1.d \
./hw1/q2.d \
./hw1/q3.d 


# Each subdirectory must supply rules for building sources it contributes
hw1/%.o: ../hw1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


