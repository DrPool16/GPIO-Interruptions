################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/uart/fsl_adapter_lpuart.c 

C_DEPS += \
./component/uart/fsl_adapter_lpuart.d 

OBJS += \
./component/uart/fsl_adapter_lpuart.o 


# Each subdirectory must supply rules for building sources it contributes
component/uart/%.o: ../component/uart/%.c component/uart/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_K32L2B31VLH0A -DCPU_K32L2B31VLH0A_cm0plus -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\elmes\Documents\MCUXpressoIDE_25.6.136\workspace\GPIO_+_Interruptions\board" -I"C:\Users\elmes\Documents\MCUXpressoIDE_25.6.136\workspace\GPIO_+_Interruptions\source" -I"C:\Users\elmes\Documents\MCUXpressoIDE_25.6.136\workspace\GPIO_+_Interruptions\drivers" -I"C:\Users\elmes\Documents\MCUXpressoIDE_25.6.136\workspace\GPIO_+_Interruptions\utilities\str" -I"C:\Users\elmes\Documents\MCUXpressoIDE_25.6.136\workspace\GPIO_+_Interruptions\component\serial_manager" -I"C:\Users\elmes\Documents\MCUXpressoIDE_25.6.136\workspace\GPIO_+_Interruptions\CMSIS" -I"C:\Users\elmes\Documents\MCUXpressoIDE_25.6.136\workspace\GPIO_+_Interruptions\CMSIS\m-profile" -I"C:\Users\elmes\Documents\MCUXpressoIDE_25.6.136\workspace\GPIO_+_Interruptions\device" -I"C:\Users\elmes\Documents\MCUXpressoIDE_25.6.136\workspace\GPIO_+_Interruptions\component\lists" -I"C:\Users\elmes\Documents\MCUXpressoIDE_25.6.136\workspace\GPIO_+_Interruptions\component\uart" -I"C:\Users\elmes\Documents\MCUXpressoIDE_25.6.136\workspace\GPIO_+_Interruptions\utilities\debug_console" -I"C:\Users\elmes\Documents\MCUXpressoIDE_25.6.136\workspace\GPIO_+_Interruptions\device\periph2" -I"C:\Users\elmes\Documents\MCUXpressoIDE_25.6.136\workspace\GPIO_+_Interruptions\utilities\debug_console\config" -I"C:\Users\elmes\Documents\MCUXpressoIDE_25.6.136\workspace\GPIO_+_Interruptions\utilities" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-uart

clean-component-2f-uart:
	-$(RM) ./component/uart/fsl_adapter_lpuart.d ./component/uart/fsl_adapter_lpuart.o

.PHONY: clean-component-2f-uart

