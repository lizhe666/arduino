#include "Arduino.h"
#include <SoftwareSerial.h>

#define MAX_ATTEMPTS 10

class PMS1003 {

private:
  SoftwareSerial* serialPM25;
  byte bufferBytes[32];
  int lastPM10;
  int lastPM25;
  int lastPM100;
  
public:
  PMS1003(); 
  ~PMS1003(); 
  void begin(uint8_t, uint8_t);
  bool read(void);
  int getLastPM10(void);
  int getLastPM25(void);
  int getLastPM100(void);
  int bytesToInt(byte h, byte l);
};