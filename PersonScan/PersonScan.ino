#include "Arduino.h"
#include "ESP8266.h"
ESP8266 esp8266;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  esp8266.init(&Serial3, 13);
  //esp8266.smartConfig("1");
  //esp8266.configWithPwd("xiaoduola","baomazfour");
  esp8266.configWithPwd("chuanke-qa", "chuanketest");


  pinMode(8, INPUT);
}

void loop() {
  int info = digitalRead(8);
  Serial.println(info);

  String host = F("www.ixinfeng.com");
  String path = F("/send");
  String data = "?uid=100&t=" + (String) info;
                
  String retJson = esp8266.httpGet(host, 80, path + data);
  Serial.println(retJson);
  delay(10000);

}
