#ifndef PM25HARDSERIAL_H
#define PM25HARDSERIAL_H

#include "Arduino.h"
#define PM25_MAX_ATTEMPTS 3

//带有温湿度的，是40字节
#define BUFFER_SIZE 40
//无温湿度的，是32字节
//#define BUFFER_SIZE 32

class Pm25HardSerial {

private:
  HardwareSerial* serialPM25;
  int sleepPin; //休眠的指针号
  byte bufferBytes[BUFFER_SIZE];
  int lastPM10 = 0;
  int lastPM25 = 0;
  int lastPM100 = 0;
  float lastHCHO = 0.0;
  float lastT = 0.0;
  float lastH = 0.0;
public:
  void begin(HardwareSerial*,int);
  bool read(void);
  int getLastPM10(void);
  int getLastPM25(void);
  int getLastPM100(void);
  float getLastHCHO(void);
  float getLastT(void);
  float getLastH(void);
  void sleep(bool);
  int bytesToInt(byte h, byte l);
};

#endif
