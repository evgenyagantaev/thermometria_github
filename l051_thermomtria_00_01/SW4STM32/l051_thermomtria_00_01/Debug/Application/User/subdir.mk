################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Src/gpio.c \
D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Src/main.c \
D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Src/spi.c \
D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Src/stm32l0xx_hal_msp.c \
D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Src/stm32l0xx_it.c \
D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Src/tim.c \
D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Src/usart.c 

OBJS += \
./Application/User/gpio.o \
./Application/User/main.o \
./Application/User/spi.o \
./Application/User/stm32l0xx_hal_msp.o \
./Application/User/stm32l0xx_it.o \
./Application/User/tim.o \
./Application/User/usart.o 

C_DEPS += \
./Application/User/gpio.d \
./Application/User/main.d \
./Application/User/spi.d \
./Application/User/stm32l0xx_hal_msp.d \
./Application/User/stm32l0xx_it.d \
./Application/User/tim.d \
./Application/User/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/gpio.o: D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Src/gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Inc" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/STM32L0xx_HAL_Driver/Inc" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/CMSIS/Include" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/CMSIS/Device/ST/STM32L0xx/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/main.o: D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Inc" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/STM32L0xx_HAL_Driver/Inc" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/CMSIS/Include" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/CMSIS/Device/ST/STM32L0xx/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/spi.o: D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Src/spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Inc" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/STM32L0xx_HAL_Driver/Inc" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/CMSIS/Include" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/CMSIS/Device/ST/STM32L0xx/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32l0xx_hal_msp.o: D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Src/stm32l0xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Inc" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/STM32L0xx_HAL_Driver/Inc" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/CMSIS/Include" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/CMSIS/Device/ST/STM32L0xx/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32l0xx_it.o: D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Src/stm32l0xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Inc" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/STM32L0xx_HAL_Driver/Inc" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/CMSIS/Include" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/CMSIS/Device/ST/STM32L0xx/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/tim.o: D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Src/tim.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Inc" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/STM32L0xx_HAL_Driver/Inc" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/CMSIS/Include" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/CMSIS/Device/ST/STM32L0xx/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usart.o: D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Src/usart.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Inc" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/STM32L0xx_HAL_Driver/Inc" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/CMSIS/Include" -I"D:/workspace/stm32/thermometria_github/l051_thermomtria_00_01/Drivers/CMSIS/Device/ST/STM32L0xx/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


