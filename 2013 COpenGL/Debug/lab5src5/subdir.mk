################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lab5src5/Lab5C5.c 

LAB55OBJS += \
./lab5src4/Lab5C4.o 

OBJS += \
./lab5src5/Lab5C5.o 

C_DEPS += \
./lab5src5/Lab5C5.d 


# Each subdirectory must supply rules for building sources it contributes
lab5src5/%.o: ../lab5src5/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


