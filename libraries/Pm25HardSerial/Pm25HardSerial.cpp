#include "Pm25HardSerial.h"

void Pm25HardSerial::begin(HardwareSerial* serial, int pin) {
  serialPM25 = serial;
  serialPM25->begin(9600);
  sleepPin = pin;
  pinMode(sleepPin,OUTPUT);
}

bool Pm25HardSerial::read(void) {
	for ( int attempts = 0; attempts < PM25_MAX_ATTEMPTS; attempts++ ) {
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

				int checksum = 0;
				for(int j=0;j<=29;j++){
					checksum += (int)bufferBytes[j];
					//Serial.println(j);

				}
				//Serial.println(checksum);
				//Serial.println(bytesToInt(bufferBytes[30], bufferBytes[31]));
				if(checksum == bytesToInt(bufferBytes[30], bufferBytes[31])){
					lastPM10 = bytesToInt(bufferBytes[10], bufferBytes[11]);
					lastPM25 = bytesToInt(bufferBytes[12], bufferBytes[13]);
					lastPM100 = bytesToInt(bufferBytes[14], bufferBytes[15]);
					lastHCHO = ((float)(bytesToInt(bufferBytes[28], bufferBytes[29]))) / 1000.0;
					//Serial.println("true");
					//Serial.println(bytesToInt(bufferBytes[12], bufferBytes[13]));
				
					return true;
				}else{
					return false;
				}
			}
			i++;
			delay(10);
		}

		//Serial.print("attempts=");
		//Serial.print(attempts);
		//Serial.println("___");
		//Serial.println(i);

	}
	return false;
}

int Pm25HardSerial::getLastPM10(void) {
	return lastPM10;
}

int Pm25HardSerial::getLastPM25(void) {
	return lastPM25;
}

int Pm25HardSerial::getLastPM100(void) {
	return lastPM100;
}

float Pm25HardSerial::getLastHCHO(void) {
	return lastHCHO;
}

void Pm25HardSerial::sleep(bool b){
	if(b){
		digitalWrite(sleepPin,LOW);
	}else{
		digitalWrite(sleepPin,HIGH);
	}
}

/**
* byte数组中取int数值
*/
int Pm25HardSerial::bytesToInt(byte h, byte l) {
  int value = (int) ((l & 0xFF) | ((h << 8) & 0xFF00));
  return value;
}
