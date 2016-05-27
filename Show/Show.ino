//DFRobot.com
//Compatible with the Arduino IDE 1.0
//Library version:1.1


/*

read form https://www.arduino.cc/en/Reference/Wire

Arduino各型号使用I2C通信的引脚说明

Arduino中使用I2C通信可直接调用Wire.h库。这个库允许Arduino链接其他I2C设备。 链接线有两条，分别是SDA(数据行)和SCI(时钟线)。
下面是各型号Arduino的I2C对应引脚：
Arduino Board：I2C / TWI pins
Arduino Uno/Ethernet：A4 (SDA), A5 (SCL)
Arduino Mega2560：20 (SDA), 21 (SCL)
Arduino Leonardo：2 (SDA), 3 (SCL)
Arduino Due：20 (SDA), 21 (SCL), SDA1, SCL1

*/




#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

void setup(){
  
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  
  lcd.home();
  lcd.print("Hello world...");
  lcd.setCursor(0, 1);
  lcd.print("dfrobot.com");
  
}

int backlightState = LOW;
long previousMillis = 0;
long interval = 1000;
  
void loop(){
  
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;   

    if (backlightState == LOW)
      backlightState = HIGH;
    else
      backlightState = LOW;

    if(backlightState == HIGH)  lcd.backlight();
    else lcd.noBacklight();
  }
}
