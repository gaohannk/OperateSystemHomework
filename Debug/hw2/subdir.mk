################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hw2/q1.c \
../hw2/q2.c \
../hw2/q3.c 

OBJS += \
./hw2/q1.o \
./hw2/q2.o \
./hw2/q3.o 

C_DEPS += \
./hw2/q1.d \
./hw2/q2.d \
./hw2/q3.d 


# Each subdirectory must supply rules for building sources it contributes
hw2/%.o: ../hw2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


