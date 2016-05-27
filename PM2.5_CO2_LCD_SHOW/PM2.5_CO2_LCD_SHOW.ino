/**
按照PDF的说明，接正极负极两根线，以及传感器的TX输出线到Arduino板子的输入RX即可，其余的都不需要连接
UNO的板子必须先拔掉RX上的输入，然后才才能上传，上传后再插入线接收数据，  否则无法写入数据
*/
////////////////////////////
//LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif
LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display
// LCD
///////////////////////////

#include "SoftwareSerial.h"
#include <PMS1003.h>
PMS1003 pms1003;
#include <T6603.h>  //download from   http://forum.arduino.cc/index.php?topic=289428.0
T6603 t6603;
#include <VOC_MS1100_P211.h> 
VOC_MS1100_P211 sensor(3);
#include "DHT.h"
#define DHTPIN 8     // what pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  //init co2;
  t6603.begin(10/*port 2*/, 11/*port 1*/);  
  //init pm2.5
  pms1003.begin(2/*arduino的输入端（接收端）*/, 3); 
  //init dht
  dht.begin();
  
  //////////////////////////////////////
  // LCD  initialize the lcd 
  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.setCursor(0, 1);
  // LCD
  //////////////////////////////////////  
  
  pinMode(7, OUTPUT); // sets the redPin to be an output 
  pinMode(6, OUTPUT); // sets the greenPin to be an output 
  pinMode(5, OUTPUT); // sets the bluePin to be an output 
  
  pinMode(13, OUTPUT);
}

void loop() {
  //read the last data
  pms1003.read();  //TODO  why  this line need to be put first???
  delay(500);// pm25 need to wait at least 500  
  //int CO2 = t6603.getCO2();
  delay(500);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  
  //Serial.print("CO2=");
  //Serial.println(CO2);
  Serial.print("PM1.0=");
  Serial.println(pms1003.getLastPM10());
  Serial.print("PM2.5=");
  Serial.println(pms1003.getLastPM25());
  Serial.print("PM10=");
  Serial.println(pms1003.getLastPM100());
  Serial.println("_______________________");
  
  lcd.home();
  lcd.clear();
  //lcd.print("CO2=");
 // lcd.print(CO2);
  lcd.setCursor(0, 1);
  lcd.print("PM25=");
  lcd.print(pms1003.getLastPM25());
  
  lcd.setCursor(12,0);
  lcd.print(sensor.read(true));
  
  
  lcd.setCursor(10,1);
  lcd.print(h);
  lcd.print("%");
  lcd.print(t);
  lcd.print("C");
  
  
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");
  
  if(sensor.read(false)>0.08){
    color(255, 0, 0); // turn the RGB LED red  
    alarm(3);
    delay(300);  
  }else{
    color(255,255,255); // turn off the RGB LED
  }
  
 // if(CO2>1200){
 //   color(0, 0, 255); // turn the RGB LED blue
 //   alarm(2);
 //   delay(300);  
 // }else{
 //   color(255,255,255); // turn off the RGB LED
 // }
  
  if(pms1003.getLastPM25()>80){
    color(0,255, 0); // turn the RGB LED green  
    alarm(1);
    delay(300);  
  }else{
    color(255,255,255); // turn off the RGB LED
  }
  
}


void color (unsigned char red, unsigned char green, unsigned char blue)     // the color generating function  
{    
          analogWrite(7, 255-red);   
          analogWrite(6, 255-blue); 
          analogWrite(5, 255-green); 
}  

void alarm(int times){
  for(int i=0;i<times;i++){
    digitalWrite(13,HIGH);
    delay(100);
    digitalWrite(13,LOW);
    delay(100);
  
  }
}
     
