#include "T6603HardSerial.h"


void T6603HardSerial::begin(HardwareSerial* serial) {
  _serial = serial;
  _serial->begin(19200);
}

int T6603HardSerial::getCO2(void) {
  _serial->write(FLAG);
  _serial->write(BRDCST);
  _serial->write(0x02);
  _serial->write(CMD_READ); 
  _serial->write(CO2_PPM);
  delay(50);

  for ( int attempts = 0; attempts < T6603_MAX_ATTEMPTS; attempts++ ) {
    //批量读取数据源5个字节
	int i = 0;    
	while (_serial->available()) {
		//Serial.print(i);
		bufferBytes[i] = _serial->read();
		//起始确认，有可能不是，得根据后续的校验
		if(i==2){
			if(bufferBytes[0]==0xFF&&bufferBytes[1]==0xFA&&bufferBytes[2]==0x02){
				//起始符号正确
			}else{
				i--; //读取4个字节后，验证，如果不正确，则回退一位重新开始
				bufferBytes[0] = bufferBytes[1]; 
				bufferBytes[1] = bufferBytes[2];
				bufferBytes[2] = NULL;
			}
		}
		if(i>=4){
			int co2 = bytesToInt(bufferBytes[3], bufferBytes[4]);
			//if(co2>0){
			//	_lastReading = co2;
			//}
			//return _lastReading;
			return co2;
		}
		i++;
		delay(10);
	}
  }  
 // return _lastReading;
  return -100;
}

byte T6603HardSerial::getStatus(void) {
  _serial->write(FLAG);
  _serial->write(BRDCST);
  _serial->write(0x01);
  _serial->write(CMD_STATUS); 
  delay(50);

  for ( int attempts = 0; attempts < T6603_MAX_ATTEMPTS; attempts++ ) {
    byte reading[4]; 
    int bytesRead = 0;    
    
    while ( _serial->available() && bytesRead < 4) {
      reading[bytesRead] = _serial->read();
      bytesRead++;
      delay(10);
    }

    if ( reading[0] == 0xFF && reading[1] == 0xFA ) {
      return ( reading[3] );
    }
  }
  
  return (NULL);
}

void T6603HardSerial::setIdle(bool onOff) {
  byte cmd = onOff ? 0x01 : 0x02;
  
  _serial->write(FLAG);
  _serial->write(BRDCST);
  _serial->write(0x02);
  _serial->write(CMD_IDLE); 
  _serial->write(cmd);
  delay(50);

  for ( int attempts = 0; attempts < T6603_MAX_ATTEMPTS; attempts++ ) {
    byte reading[3]; 
    int bytesRead = 0;    
    
    while ( _serial->available() && bytesRead < 3) {
      reading[bytesRead] = _serial->read();
      bytesRead++;
      delay(10);
    }

    if ( reading[0] == 0xFF && reading[1] == 0xFA ) {
      return;
    }
  }    
}

/**
* byte数组中取int数值
*/
int T6603HardSerial::bytesToInt(byte h, byte l) {
  int value = (int) ((l & 0xFF) | ((h << 8) & 0xFF00));
  return value;
}
