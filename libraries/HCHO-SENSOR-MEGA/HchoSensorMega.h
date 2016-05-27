#include "Arduino.h"

#define MAX_ATTEMPTS 10

class HchoSensorMega {

private:
  HardwareSerial* serialHCHO;
  byte bufferBytes[10];
  float lastHCHO = 0;
  
public:
  HchoSensorMega(); 
  ~HchoSensorMega(); 
  void begin(HardwareSerial* serial);
  float read(void);
  int bytesToInt(byte h, byte l);
};