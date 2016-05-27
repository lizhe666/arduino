#ifndef T6603HARDSERIAL_H
#define T6603HARDSERIAL_H

#include "Arduino.h"

#define T6603_MAX_ATTEMPTS 3

class T6603HardSerial {

private:
  static const byte FLAG     = 0xFF;
  static const byte BRDCST    = 0xFE;
  static const byte CMD_READ   = 0x02;
  static const byte CMD_UPDATE  = 0x03;
  static const byte CMD_STATUS  = 0xB6;
  static const byte CMD_IDLE   = 0xB9;

  static const byte CO2_PPM   = 0x03;

  HardwareSerial* _serial;
  byte bufferBytes[5];
  int _lastReading = 0;
  
  int bytesToInt(byte h, byte l);

public:
  void begin(HardwareSerial*);
  int getCO2(void);
  byte getStatus(void);
  void setIdle(bool);
};

#endif
