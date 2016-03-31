################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hw6/barrier.c \
../hw6/q1.c 

OBJS += \
./hw6/barrier.o \
./hw6/q1.o 

C_DEPS += \
./hw6/barrier.d \
./hw6/q1.d 


# Each subdirectory must supply rules for building sources it contributes
hw6/%.o: ../hw6/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


