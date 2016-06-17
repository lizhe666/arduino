#include "Pm25HardSerial.h"
Pm25HardSerial pm25HardSerial;
Pm25HardSerial pm25HardSerial1;
Pm25HardSerial pm25HardSerial2;
Pm25HardSerial pm25HardSerial3;

void setup() {
  Serial.begin(9600);
  pm25HardSerial1.begin(&Serial1, 7);
  pm25HardSerial1.sleep(false);

  pm25HardSerial2.begin(&Serial2, 7);
  pm25HardSerial2.sleep(false);

  pm25HardSerial3.begin(&Serial3, 7);
  pm25HardSerial3.sleep(false);

  pm25HardSerial.begin(&Serial, 7);
  pm25HardSerial.sleep(false);

}
void readData(Pm25HardSerial pm25HardSerial, String info) {
  if (pm25HardSerial.read()) {
    Serial.print(info);
    Serial.print("\t\tPM1.0=");
    Serial.print(pm25HardSerial.getLastPM10());
    Serial.print("\t\tPM2.5=");
    Serial.print(pm25HardSerial.getLastPM25());
    Serial.print("\t\tPM10=");
    Serial.print(pm25HardSerial.getLastPM100());
    Serial.print("\t\tHCHO=");
    Serial.print(pm25HardSerial.getLastHCHO());
    Serial.print("\t\tT=");
    Serial.print(pm25HardSerial.getLastT());
    Serial.print("\t\tH=");
    Serial.println(pm25HardSerial.getLastH());
    //Serial.println("_______________________");
  } else {
    Serial.print(info);
    Serial.println("\t\tfalse");
  }

}
void loop() {
  readData(pm25HardSerial1, "Serial1");
  readData(pm25HardSerial2, "Serial2");
  readData(pm25HardSerial3, "Serial3");
  readData(pm25HardSerial, "Serial");
  Serial.println("_______________________________________________________________________________________________________________________");
  delay(1000); // pm25 need to wait at least 500
}
