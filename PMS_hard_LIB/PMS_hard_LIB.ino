#include "Pm25HardSerial.h"
Pm25HardSerial pm25HardSerial;

void setup() {
  Serial.begin(9600);
  pm25HardSerial.begin(&Serial2,7);  
  pm25HardSerial.sleep(false);
  Serial.print("setup");

}

void loop() {
  if(pm25HardSerial.read()){
    Serial.print("PM1.0=");
    Serial.println(pm25HardSerial.getLastPM10());
    Serial.print("PM2.5=");
    Serial.println(pm25HardSerial.getLastPM25());
    Serial.print("PM10=");
    Serial.println(pm25HardSerial.getLastPM100());
    Serial.print("HCHO=");
    Serial.println(pm25HardSerial.getLastHCHO());
    Serial.print("T=");
    Serial.println(pm25HardSerial.getLastT());
    Serial.print("H=");
    Serial.println(pm25HardSerial.getLastH());
    Serial.println("_______________________");
    delay(500); // pm25 need to wait at least 500
  }
}
