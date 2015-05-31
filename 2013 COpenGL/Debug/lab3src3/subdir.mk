################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lab3src3/Lab3C03.c 

LAB33OBJS += \
./lab3src3/Lab3C03.o 

OBJS += \
./lab3src3/Lab3C03.o 

C_DEPS += \
./lab3src3/Lab3C03.d 


# Each subdirectory must supply rules for building sources it contributes
lab3src3/%.o: ../lab3src3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


