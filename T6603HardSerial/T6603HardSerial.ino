//comments by lizhe:  use this chip,only need to use 4 ports, and is shown in the setup function down
//the port number is from left to right
#include <T6603HardSerial.h>
T6603HardSerial sensor;

void setup() {
  //port 3    5V+
  //port 4    GND
  Serial.begin(19200);
  Serial.println("Initing...");
  sensor.begin(&Serial3);
}

void loop() {
  Serial.print("co2.getStatus=");
  Serial.println(sensor.getStatus());
  Serial.print("Co2: ");
  Serial.print(sensor.getCO2());
  Serial.println(" PPM");
  delay(1000);

  Serial.println(sensor.getStatus());



}
