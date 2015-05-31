################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lab7src/Lab7C1.c 

LAB7OBJS += \
./lab7src/Lab7C1.o 

OBJS += \
./lab7src/Lab7C1.o 

C_DEPS += \
./lab7src/Lab7C1.d 


# Each subdirectory must supply rules for building sources it contributes
lab7src/%.o: ../lab7src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


