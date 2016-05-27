#include "SoftwareSerial.h"
#include "NewSoftSerial.h"
#include <HchoSensor.h>
HchoSensor hchoSensor;

/*
Not all pins on the Mega and Mega 2560 support change interrupts, so only the following can be used for RX: 10, 11, 12, 13, 14, 15, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68), A15 (69)

*/
void setup() {
  Serial.begin(9600);
  hchoSensor.begin(10/*arduino的输入端（接收端）*/,11); 
}

void loop() {
  Serial.println(hchoSensor.read());
  delay(500); // 

}
