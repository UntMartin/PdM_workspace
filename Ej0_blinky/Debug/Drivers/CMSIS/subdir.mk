################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/pato/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.2/Projects/STM32F429ZI-Nucleo/Examples/GPIO/GPIO_IOToggle/Src/system_stm32f4xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32f4xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32f4xx.o: /home/pato/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.2/Projects/STM32F429ZI-Nucleo/Examples/GPIO/GPIO_IOToggle/Src/system_stm32f4xx.c Drivers/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Inc -I"/home/pato/STM32CubeIDE/workspace_1.7.0/Ej0_blinky/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/pato/STM32CubeIDE/workspace_1.7.0/Ej0_blinky/Drivers/CMSIS/Include" -I"/home/pato/STM32CubeIDE/workspace_1.7.0/Ej0_blinky/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/pato/STM32CubeIDE/workspace_1.7.0/Ej0_blinky/Drivers/BSP/STM32F4xx_Nucleo_144" -I"/home/pato/STM32CubeIDE/workspace_1.7.0/Ej0_blinky/Drivers/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

