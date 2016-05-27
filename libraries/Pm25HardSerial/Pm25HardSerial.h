#ifndef PM25HARDSERIAL_H
#define PM25HARDSERIAL_H

#include "Arduino.h"
#define PM25_MAX_ATTEMPTS 3

class Pm25HardSerial {

private:
  HardwareSerial* serialPM25;
  int sleepPin; //休眠的指针号
  byte bufferBytes[32];
  int lastPM10 = 0;
  int lastPM25 = 0;
  int lastPM100 = 0;
  float lastHCHO = 0.0;
public:
  void begin(HardwareSerial*,int);
  bool read(void);
  int getLastPM10(void);
  int getLastPM25(void);
  int getLastPM100(void);
  float getLastHCHO(void);
  void sleep(bool);
  int bytesToInt(byte h, byte l);
};

#endif
