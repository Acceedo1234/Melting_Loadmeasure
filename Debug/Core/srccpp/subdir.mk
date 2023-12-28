################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/srccpp/main.cpp 

OBJS += \
./Core/srccpp/main.o 

CPP_DEPS += \
./Core/srccpp/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/srccpp/%.o Core/srccpp/%.su: ../Core/srccpp/%.cpp Core/srccpp/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"D:/PROGRAM/Naveen/melting/Loadmeasure-20.12.23/Core/srccpp" -I"D:/PROGRAM/Naveen/melting/Loadmeasure-20.12.23/Core/srccpp/Common" -I"D:/PROGRAM/Naveen/melting/Loadmeasure-20.12.23/Core/srccpp/DisplayCPP" -I"D:/PROGRAM/Naveen/melting/Loadmeasure-20.12.23/Core/srccpp/Ethernet" -I"D:/PROGRAM/Naveen/melting/Loadmeasure-20.12.23/Core/srccpp/Modbus" -I"D:/PROGRAM/Naveen/melting/Loadmeasure-20.12.23/Core/srccpp/OfflineStorage" -I"D:/PROGRAM/Naveen/melting/Loadmeasure-20.12.23/Core/srccpp/Shift" -I"D:/PROGRAM/Naveen/melting/Loadmeasure-20.12.23/Core/srccpp/WifiEsp8266" -I"D:/PROGRAM/Naveen/melting/Loadmeasure-20.12.23/Core/srccpp/BussinessLogic" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-srccpp

clean-Core-2f-srccpp:
	-$(RM) ./Core/srccpp/main.d ./Core/srccpp/main.o ./Core/srccpp/main.su

.PHONY: clean-Core-2f-srccpp

