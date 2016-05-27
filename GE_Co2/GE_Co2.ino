//comments by lizhe:  use this chip,only need to use 4 ports, and is shown in the setup function down
//the port number is from left to left
#include "SoftwareSerial.h"
#include <T6603.h>  //download from   http://forum.arduino.cc/index.php?topic=289428.0
T6603 sensor;

void setup() {
  //port 3    5V+
  //port 4    GND
  Serial.begin(19200);
  Serial.println("Initing...");
  sensor.begin(15/*port 2*/, 14/*port 1*/);
}

void loop() {
  //Serial.print("Co2: ");
  Serial.println(sensor.getStatus());

  Serial.println(sensor.getCO2());
  //Serial.println(" PPM");
  delay(2000);
}
