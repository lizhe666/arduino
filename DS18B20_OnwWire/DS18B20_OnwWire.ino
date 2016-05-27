#include <DS18B20_OneWire.h>
#include "OneWire.h"

DS18B20_OneWire ds18b20 = DS18B20_OneWire(10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float celsius = ds18b20.getLastCelsius();
  Serial.println(celsius);
}
