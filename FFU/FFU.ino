#include "Arduino.h"

#include "ESP8266.h"
ESP8266 esp8266;

#define NEW_AIR_PIN 10

String lastStatusNewAir = "1";

void setup() {
  Serial.begin(115200);
  Serial.println(((String)"setup in"));

  pinMode(NEW_AIR_PIN, OUTPUT);
  
  esp8266.init(&Serial3, 13);
  //esp8266.smartConfig("1");
  esp8266.configWithPwd("xiaoduola","baomazfour");
  Serial.println(F("setup out"));
}
//---------------------------------------------------------------------
void loop() {
  delay(5000);
  String host = F("www.ixinfeng.com");
  String path = F("/st/Decision?uid=4&type=EQUIP_1&status=");

  String html = esp8266.httpGet(host, 80, path + lastStatusNewAir);

  Serial.println(html);

  if (html.equals("1")) {
    lastStatusNewAir = "1";
    Serial.println("NEW_AIR: ON");
    digitalWrite(NEW_AIR_PIN, HIGH);
  } else if (html.equals("9")) {   //进入警戒模式！！ 如果可能，开启大风量
    lastStatusNewAir = "9";
    Serial.println("NEW_AIR: ON-Warning");
    digitalWrite(NEW_AIR_PIN, HIGH);
  } else if (html.equals("-1")) {  //空气良好，可以关闭新风，节约能源
    lastStatusNewAir = "-1";
    Serial.println("NEW_AIR: OFF");
    digitalWrite(NEW_AIR_PIN, LOW);
  } else if (html.equals("0")) {   //no change
    Serial.println("NEW_AIR: No Change!");
  } else {
    lastStatusNewAir = "1";
    Serial.println("NEW_AIR: wifi error, open by default!");
    digitalWrite(NEW_AIR_PIN, HIGH);
  }
  
  delay(30000);


}
