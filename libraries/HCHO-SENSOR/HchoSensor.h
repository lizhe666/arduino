#include "Arduino.h"
#include <SoftwareSerial.h>

#define MAX_ATTEMPTS 10

class HchoSensor {

private:
  SoftwareSerial* serialHCHO;
 // HardwareSerial* serialHCHO;
  byte bufferBytes[10];
  float lastHCHO = 0;
  
public:
  HchoSensor(); 
  ~HchoSensor(); 
  void begin(uint8_t, uint8_t);
  void begin(HardwareSerial* serial);
  float read(void);
  int bytesToInt(byte h, byte l);
};