#include "SoftwareSerial.h"
#include <HchoSensorMega.h>
HchoSensorMega hchoSensorMega;

void setup() {
  Serial.begin(9600);
  hchoSensorMega.begin(&Serial3); 
}

void loop() {
  Serial.println(hchoSensorMega.read());
  delay(500); // 

}
