#include "HchoSensorMega.h"

HchoSensorMega::HchoSensorMega() {
}

HchoSensorMega::~HchoSensorMega() {
  if ( NULL != serialHCHO ) {
    delete serialHCHO;
    serialHCHO = NULL;
  }
}

//rx 代表的是arduino的输入端（接收端）
void HchoSensorMega::begin(HardwareSerial* serial) {
  serialHCHO = serial;
  serialHCHO->begin(9600);
}

/*
主机发送查询监测数据指令
0x42 0x4d 0x01 0x00 0x00 0x00 0x90
模块返回数据：
0x42 0x4d 0x08 0x14 0x05 0x03 0x00 0x0a 0x00 0xbd 
即 监测气体位甲醛 浓度为 0.10mg/m3
详细说明
0x42 0x4d 固定表示符号
0x08 后续发送 8 个字节数（包括自身）
0x14 监测类型表示 甲醛
0x05 数据单位标识 mg/m3
0x03 数据当量表示 100
0x00 0x0a 返回数据 0x000a = 10
实际数据=返回数据/数据当量=10/100=0.10
0x00 0xbd 数据校验高低字节
*/

float HchoSensorMega::read(void) {
	byte cmdBytes[7] = {0x42, 0x4d, 0x01, 0x00, 0x00, 0x00, 0x90};
	serialHCHO->write(cmdBytes,7);
	
	//serialHCHO->listen();
	//serialHCHO->overflow();
	for ( int attempts = 0; attempts < MAX_ATTEMPTS; attempts++ ) {
		//批量读取数据源10个字节
		int i = 0;    
		while (serialHCHO->available()) {
			//Serial.print(i);
			bufferBytes[i] = serialHCHO->read();
			//Serial.print(bufferBytes[i],HEX);
			//Serial.print(" ");
			//起始确认，有可能不是，得根据后续的校验
			if(i==4){
				if(bufferBytes[0]==0x42&&bufferBytes[1]==0x4d&&bufferBytes[2]==0x08&&bufferBytes[3]==0x14&&bufferBytes[4]==0x05){
					//起始符号正确
				}else{
					i--; //读取5个字节后，验证，如果不正确，则回退一位重新开始
					bufferBytes[0] = bufferBytes[1]; 
					bufferBytes[1] = bufferBytes[2];
					bufferBytes[2] = bufferBytes[3];
					bufferBytes[3] = bufferBytes[4];			  
					bufferBytes[4] = NULL;
				}
			}
			if(i>=9){
				lastHCHO = bytesToInt(bufferBytes[6], bufferBytes[7]);
				if(bufferBytes[5]==0x01){
					lastHCHO = lastHCHO / 1.00;
				}else if(bufferBytes[5]==0x02){
					lastHCHO = lastHCHO / 10.00;
				}else if(bufferBytes[5]==0x03){
					lastHCHO = lastHCHO / 100.00;
				}else if(bufferBytes[5]==0x04){
					lastHCHO = lastHCHO / 100.00;
				}				
				//Serial.print("lastHCHO=");
				//Serial.println(lastHCHO);
				
				return lastHCHO;
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
	return -1.0;
}

/**
* byte数组中取int数值
*/
int HchoSensorMega::bytesToInt(byte h, byte l) {
  int value = (int) ((l & 0xFF) | ((h << 8) & 0xFF00));
  return value;
}