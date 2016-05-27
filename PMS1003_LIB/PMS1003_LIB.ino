#include "SoftwareSerial.h"
#include <PMS1003.h>
PMS1003 pms1003;

void setup() {
  Serial.begin(9600);
  pms1003.begin(2/*arduino的输入端（接收端）*/, 3);  
}

void loop() {
  if(pms1003.read()){
    Serial.print("PM1.0=");
    Serial.println(pms1003.getLastPM10());
    Serial.print("PM2.5=");
    Serial.println(pms1003.getLastPM25());
    Serial.print("PM10=");
    Serial.println(pms1003.getLastPM100());
    Serial.println("_______________________");
    delay(500); // pm25 need to wait at least 500
  }
}
