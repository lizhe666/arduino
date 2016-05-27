/*
LCD  Arduino
PIN1 = GND
PIN2 = 5V
RS(CS) = 8; 
R/W(SID)= 9; 
EN(E)(CLK) = 3;
PIN15 PSB = GND;
*/
 
#include "LCD12864RSPI.h"
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )
 
//unsigned char show0[]={0xBC,0xAB,0xBF,0xCD,0xB9,0xA4,0xB7,0xBB};//极客工坊


 
void setup()
{
LCDA.Initialise(); // 屏幕初始化
delay(100);
pinMode(13, OUTPUT);

analogWrite(13,10);
}
 
void loop()
{
  unsigned char* show0 =(unsigned char*)"i love Mengmeng!";
unsigned char show1[]="www.ixinfeng.com";
  
LCDA.CLEAR();//清屏
delay(100);//必须要有延，否则会出现乱码

LCDA.DisplayString(0,0,show0,16);//第一行第三格开始，显示文字极客工坊

delay(100);
LCDA.DisplayString(1,0,show1,16);//第一行第三格开始，显示文字极客工坊


delay(100);
LCDA.DisplayString(2,0,show1,16);//第一行第三格开始，显示文字极客工坊

delay(100);
LCDA.DisplayString(3,0,show1,AR_SIZE(show1));;//第三行第二格开始，显示文字geek-workshop
delay(1000);

LCDA.CLEAR();//清屏
//LCDA.DrawFullScreen(logo0);
delay(1000);
}

