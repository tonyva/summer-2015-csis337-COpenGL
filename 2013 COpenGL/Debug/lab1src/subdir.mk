################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lab1src/COpenGL01.c 

LAB1OBJS += \
./lab1src/COpenGL01.o 

OBJS += \
./lab1src/COpenGL01.o 

C_DEPS += \
./lab1src/COpenGL01.d 


# Each subdirectory must supply rules for building sources it contributes
lab1src/%.o: ../lab1src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


