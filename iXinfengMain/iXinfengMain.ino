#include "LCD12864RSPI.h"

#include "DS18B20_S.h"
DS18B20_S  ds(10);//pin10

#include <Pm25HardSerial.h>
Pm25HardSerial pms1003;
Pm25HardSerial pms5003;

unsigned char show1[]={0xCE,0xC2,0xB6,0xC8};//温度

void setup() {
  Serial.begin(9600);
  //init pm2.5
  pms5003.begin(&Serial2,11);
  pms1003.begin(&Serial3,12);
  
  //
  ds.start();//开始测量（所有传感器）
  //restartLcd();
  

  Serial.print("In Setup");

  pms1003.sleep(false);
  pms5003.sleep(false);
    
}

int counter = 1;
void restartLcd(){
  //////////////////////////////////////
  // LCD  initialize the lcd
  LCDA.Initialise(); // 屏幕初始化
  pinMode(13, OUTPUT);
  analogWrite(13, 30); // 背光亮度，TODO 可以根据光线传感器数据调节背，也可以直接关闭背光
  // LCD
  //////////////////////////////////////
}
void(* resetFunc) (void) = 0;



void loop() {
  //read the last data
  pms1003.read();  //
  delay(500);// pm25 need to wait at least 500
  pms5003.read();  //
  delay(500);



  float t = ds.get();

  Serial.print("PM2.5_1=");
  Serial.println(pms1003.getLastPM25());
  Serial.print("PM2.5_2=");
  Serial.println(pms5003.getLastPM25());
  Serial.println("_______________________");

  //LCDA.CLEAR();//清屏
  /*
  char* line0 = new char[16];
  sprintf(line0,"PM25_OUT=%d",pms1003.getLastPM25());
 // LCDA.DisplayString(0, 0, (unsigned char*)line0, strlen(line0));
  
  char* line1 = new char[16];
  sprintf(line1,"PM25_IN =%d",pms5003.getLastPM25());
 // LCDA.DisplayString(1, 0, (unsigned char*)line1, strlen(line1));
  
  
 // LCDA.DisplayString(2,0,show1,sizeof(show1));//第一行第1格开始，显示文字“当前环境温度”
  char* line2 = new char[4];
  dtostrf(t, 4, 2, line2);  // 相當於 %4.2f
 // LCDA.DisplayString(2, 3, (unsigned char*)line2, strlen(line2));
  
 // LCDA.DisplayString(3,0,(unsigned char*)"HCHO=",5);
  char* line3 = new char[4];
  dtostrf(pms5003.getLastHCHO(), 4, 2, line3);  // 相當於 %4.2f
 // LCDA.DisplayString(3, 3, (unsigned char*)line3, strlen(line3));
  
  
  //unsigned char* line3 = (unsigned char*)("www.iXinFeng.com");
  //LCDA.DisplayString(3, 0, line3, 16);
*/
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  
  Serial.println(millis());
  if(counter++ == 10){
    //  resetFunc();
      return;
  }

}

