################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Users/lizhe07/Documents/Arduino/libraries/Pm25HardSerial/._Pm25HardSerial.cpp \
C:/Users/lizhe07/Documents/Arduino/libraries/Pm25HardSerial/Pm25HardSerial.cpp 

LINK_OBJ += \
./libraries/Pm25HardSerial/._Pm25HardSerial.cpp.o \
./libraries/Pm25HardSerial/Pm25HardSerial.cpp.o 

CPP_DEPS += \
./libraries/Pm25HardSerial/._Pm25HardSerial.cpp.d \
./libraries/Pm25HardSerial/Pm25HardSerial.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/Pm25HardSerial/._Pm25HardSerial.cpp.o: C:/Users/lizhe07/Documents/Arduino/libraries/Pm25HardSerial/._Pm25HardSerial.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:\eclipseArduino\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"D:\eclipseArduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"D:\eclipseArduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Users\lizhe07\Documents\Arduino\libraries\UTFT" -I"C:\Users\lizhe07\Documents\Arduino\libraries\T6603HardSerial" -I"C:\Users\lizhe07\Documents\Arduino\libraries\DHT" -I"C:\Users\lizhe07\Documents\Arduino\libraries\Pm25HardSerial" -I"C:\Users\lizhe07\Documents\Arduino\libraries\ESP8266" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

libraries/Pm25HardSerial/Pm25HardSerial.cpp.o: C:/Users/lizhe07/Documents/Arduino/libraries/Pm25HardSerial/Pm25HardSerial.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:\eclipseArduino\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"D:\eclipseArduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"D:\eclipseArduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Users\lizhe07\Documents\Arduino\libraries\UTFT" -I"C:\Users\lizhe07\Documents\Arduino\libraries\T6603HardSerial" -I"C:\Users\lizhe07\Documents\Arduino\libraries\DHT" -I"C:\Users\lizhe07\Documents\Arduino\libraries\Pm25HardSerial" -I"C:\Users\lizhe07\Documents\Arduino\libraries\ESP8266" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


