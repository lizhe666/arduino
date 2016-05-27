#include <SoftwareSerial.h>
#include "PMS1003.h"

PMS1003::PMS1003() {
}

PMS1003::~PMS1003() {
  if ( NULL != serialPM25 ) {
    delete serialPM25;
    serialPM25 = NULL;
  }
}

//rx 代表的是arduino的输入端（接收端）
void PMS1003::begin(uint8_t rx, uint8_t tx) {
  serialPM25 = new SoftwareSerial(rx, tx);
  serialPM25->begin(9600);
}

bool PMS1003::read(void) {
	serialPM25->listen();
	serialPM25->overflow();
	for ( int attempts = 0; attempts < MAX_ATTEMPTS; attempts++ ) {
		//批量读取数据源32个字节
		int i = 0;    
		while (serialPM25->available()) {
			//Serial.print(i);
			bufferBytes[i] = serialPM25->read();
			//起始确认，有可能不是，得根据后续的校验
			if(i==3){
				if(bufferBytes[0]==0x42&&bufferBytes[1]==0x4d&&bufferBytes[2]==0x00&&bufferBytes[3]==0x1c){
					//起始符号正确
				}else{
					i--; //读取4个字节后，验证，如果不正确，则回退一位重新开始
					bufferBytes[0] = bufferBytes[1]; 
					bufferBytes[1] = bufferBytes[2];
					bufferBytes[2] = bufferBytes[3];		  
					bufferBytes[3] = NULL;
				}
			}
			if(i>=31){
				lastPM10 = bytesToInt(bufferBytes[10], bufferBytes[11]);
				lastPM25 = bytesToInt(bufferBytes[12], bufferBytes[13]);
				lastPM100 = bytesToInt(bufferBytes[14], bufferBytes[15]);
				//Serial.println("true");
				//Serial.println(bytesToInt(bufferBytes[12], bufferBytes[13]));
				
				return true;
			}
			i++;
			delay(10);
		}
		/*
		Serial.print("attempts=");
		Serial.print(attempts);
		Serial.println("___");
		Serial.println(i);				
		*/
	}
	return false;
}

int PMS1003::getLastPM10(void) {
	return lastPM10;
}

int PMS1003::getLastPM25(void) {
	return lastPM25;
}

int PMS1003::getLastPM100(void) {
	return lastPM100;
}

/**
* byte数组中取int数值
*/
int PMS1003::bytesToInt(byte h, byte l) {
  int value = (int) ((l & 0xFF) | ((h << 8) & 0xFF00));
  return value;
}