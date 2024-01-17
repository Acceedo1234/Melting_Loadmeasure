################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/srccpp/FaultHandling/Faulthandling.cpp 

OBJS += \
./Core/srccpp/FaultHandling/Faulthandling.o 

CPP_DEPS += \
./Core/srccpp/FaultHandling/Faulthandling.d 


# Each subdirectory must supply rules for building sources it contributes
Core/srccpp/FaultHandling/%.o Core/srccpp/FaultHandling/%.su: ../Core/srccpp/FaultHandling/%.cpp Core/srccpp/FaultHandling/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"D:/SourceTree/melting_loadmeasure/Core/srccpp" -I"D:/SourceTree/melting_loadmeasure/Core/srccpp/Common" -I"D:/SourceTree/melting_loadmeasure/Core/srccpp/DisplayCPP" -I"D:/SourceTree/melting_loadmeasure/Core/srccpp/Ethernet" -I"D:/SourceTree/melting_loadmeasure/Core/srccpp/Modbus" -I"D:/SourceTree/melting_loadmeasure/Core/srccpp/OfflineStorage" -I"D:/SourceTree/melting_loadmeasure/Core/srccpp/Shift" -I"D:/SourceTree/melting_loadmeasure/Core/srccpp/WifiEsp8266" -I"D:/SourceTree/melting_loadmeasure/Core/srccpp/BussinessLogic" -I"D:/SourceTree/melting_loadmeasure/Core/srccpp/FaultHandling" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-srccpp-2f-FaultHandling

clean-Core-2f-srccpp-2f-FaultHandling:
	-$(RM) ./Core/srccpp/FaultHandling/Faulthandling.d ./Core/srccpp/FaultHandling/Faulthandling.o ./Core/srccpp/FaultHandling/Faulthandling.su

.PHONY: clean-Core-2f-srccpp-2f-FaultHandling

