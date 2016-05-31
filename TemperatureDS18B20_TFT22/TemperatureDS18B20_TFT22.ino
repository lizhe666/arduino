#include "DS18B20_S.h"
//DS18B20(byte pin)  连接管脚
//传感器设定为10位模式，每次转换时间<187.5ms,如果需要12位模式，请修改库文件of ds.set(0x7F);
DS18B20_S  ds(10);//pin10


#include <UTFT.h>
extern uint8_t BigFont[];
UTFT myGLCD(QD220A, A2, A1, A5, A4, A3);


void setup() {
  Serial.begin(9600);
  Serial.println("begin!");
  // Setup the LCDM
  randomSeed(analogRead(0));
  myGLCD.InitLCD();
  myGLCD.setFont(BigFont);
  // Clear the screen and draw the frame
  myGLCD.clrScr();
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, 219, 26);
  myGLCD.setColor(64, 64, 64);
  myGLCD.fillRect(0, 149, 219, 175);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.print("Swiming Pool", CENTER, 5);
  myGLCD.setBackColor(64, 64, 64);
  myGLCD.setColor(255, 255, 0);
  myGLCD.print(">XIAO YAO<", CENTER, 154);

  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.print("Temperature", 20, 50);

}

void loop() {
  ds.start();//开始测量（所有传感器）
  float t = ds.get();

  //clear rect last
  // myGLCD.setColor(0, 0, 0);
  // myGLCD.fillRect(129, 46, 179, 146);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  delay(1000);  // Wait a few seconds between measurements.
  myGLCD.print("      ", CENTER, 92);
  myGLCD.printNumF(t, 2, CENTER, 92);


}
