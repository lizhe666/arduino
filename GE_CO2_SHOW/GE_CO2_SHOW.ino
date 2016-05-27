//comments by lizhe:  use this chip,only need to use 4 ports, and is shown in the setup function down
//the port number is from left to left
#include "SoftwareSerial.h"
#include <T6603.h>  //download from   http://forum.arduino.cc/index.php?topic=289428.0
T6603 sensor;

////////////////////////////
//LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display
// LCD
///////////////////////////


void setup() {
    //port 3    5V+
    //port 4    GND
    Serial.begin(19200);
    Serial.println("Initing...");
    sensor.begin(10/*port 2*/, 11/*port 1*/);  
    
    //////////////////////////////////////
    // LCD
    lcd.init();                      // initialize the lcd 
    lcd.backlight();
    lcd.home();
    lcd.setCursor(0, 1);
    // LCD
    ///////////////////////////

}

//////////////////////////////////////
// LCD
int backlightState = LOW;
long previousMillis = 0;
long interval = 1000;
// LCD
///////////////////////////

 
void loop() {
  int co2 =  sensor.get_co2();  
  Serial.print("Co2: ");
  Serial.print(co2);
  Serial.println(" PPM");
      lcd.clear();
      lcd.home();
      lcd.print("CO2=");
      lcd.print(co2);
      lcd.setCursor(0, 1);
      lcd.print("By iXinfeng.com");
  delay(2000);
}
