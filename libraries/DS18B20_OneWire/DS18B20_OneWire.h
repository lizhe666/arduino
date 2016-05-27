#include "OneWire.h"

class DS18B20_OneWire{
  private:
  	OneWire ds = NULL;
  	float lastCelsius = -10000.0;
  	void get();
  public:
    DS18B20_OneWire( uint8_t pin);
    float getLastCelsius();
};