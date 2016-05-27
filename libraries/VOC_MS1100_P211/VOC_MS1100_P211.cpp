#include "VOC_MS1100_P211.h"

VOC_MS1100_P211::VOC_MS1100_P211(int p) {
	port = p;
}

VOC_MS1100_P211::~VOC_MS1100_P211() {
  
}

float VOC_MS1100_P211::read(bool debug) {
	int V1 = analogRead(port);                    
	//��A0�ڶ�ȡ��ѹ���ݴ���ոմ��������ͱ���V1��ģ��ڵĵ�ѹ������ΧΪ0-5V ���ص�ֵΪ0-1024
	float vol = ((float)V1) * 5.0 / 1024.0;    
	
	//��ȩ��Ŀ��ͨ��ģ����ϳ���һ������
	float voc = 0.1091 * vol * vol - 0.0962 * vol + 0.0208 + 0.01;

	if(debug){
		Serial.print("V=");  
		Serial.print(V1);
		Serial.print("  VOL=");  
		Serial.print(vol);
		Serial.print("  VOC=");  
		Serial.println(voc);
	}
	return voc;
}
