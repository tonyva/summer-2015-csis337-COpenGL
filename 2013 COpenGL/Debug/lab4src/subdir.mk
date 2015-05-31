################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lab4src/Lab4C01.c 

LAB4OBJS += \
./lab4src/Lab4C01.o 

OBJS += \
./lab4src/Lab4C01.o 

C_DEPS += \
./lab4src/Lab4C01.d 


# Each subdirectory must supply rules for building sources it contributes
lab4src/%.o: ../lab4src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


