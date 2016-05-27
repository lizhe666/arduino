#include "VOC_MS1100_P211.h"

VOC_MS1100_P211::VOC_MS1100_P211(int p) {
	port = p;
}

VOC_MS1100_P211::~VOC_MS1100_P211() {
  
}

float VOC_MS1100_P211::read(bool debug) {
	int V1 = analogRead(port);                    
	//从A0口读取电压数据存入刚刚创建整数型变量V1，模拟口的电压测量范围为0-5V 返回的值为0-1024
	float vol = ((float)V1) * 5.0 / 1024.0;    
	
	//甲醛数目，通过模拟拟合出来一个函数
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
