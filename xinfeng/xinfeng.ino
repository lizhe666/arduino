#include "Arduino.h"

#include "ESP8266.h"
ESP8266 esp8266;

#define NEW_AIR_PIN_1 10
#define NEW_AIR_PIN_2 11
#define H_PIN 12

String lastStatusNewAir = "1";
String lastStatusH = "1";

void setup() {
  Serial.begin(115200);
  Serial.println(((String)"setup in"));

  pinMode(NEW_AIR_PIN_1, OUTPUT);
  pinMode(NEW_AIR_PIN_2, OUTPUT);
  pinMode(H_PIN, OUTPUT);

  esp8266.init(&Serial3, 13);
  esp8266.smartConfig();
  Serial.println(F("setup out"));
}
//---------------------------------------------------------------------
void loop() {
  delay(5000);
  String host = F("www.ixinfeng.com");
  String path = F("/st/Decision?uid=1&type=EQUIP_1&status=");

  String html = esp8266.httpGet(host, 80, path + lastStatusNewAir);

  //Serial.println(html);

  if (html.equals("1")) {
    lastStatusNewAir = "1";
    Serial.println("NEW_AIR: ON");
    digitalWrite(NEW_AIR_PIN_1, HIGH);
    digitalWrite(NEW_AIR_PIN_2, LOW);
  } else if (html.equals("9")) {
    lastStatusNewAir = "9";
    Serial.println("NEW_AIR: ON-Warning");
    digitalWrite(NEW_AIR_PIN_1, HIGH);
    digitalWrite(NEW_AIR_PIN_2, HIGH);
  } else if (html.equals("-1")) {
    lastStatusNewAir = "-1";
    Serial.println("NEW_AIR: OFF");
    digitalWrite(NEW_AIR_PIN_1, LOW);
    digitalWrite(NEW_AIR_PIN_2, LOW);
  } else if (html.equals("0")) {   //no change
    Serial.println("NEW_AIR: No Change!");
  } else {
    lastStatusNewAir = "1";
    Serial.println("NEW_AIR: wifi error, open by default!");
    digitalWrite(NEW_AIR_PIN_1, HIGH);
    digitalWrite(NEW_AIR_PIN_2, LOW);
  }
  
  delay(30000);


  path = F("/st/Decision?uid=1&type=EQUIP_3&status=");
  html = esp8266.httpGet(host, 80, path + lastStatusH);
  if (html.equals("1")) {
    lastStatusH = "1";
    Serial.println("H: ON");
    digitalWrite(H_PIN, HIGH);
  } else if (html.equals("9")) {
    lastStatusH = "9";
    Serial.println("H: ON-Warning");
    digitalWrite(H_PIN, HIGH);
  } else if (html.equals("-1")) {
    lastStatusH = "-1";
    Serial.println("H: OFF");
    digitalWrite(H_PIN, LOW);
  } else if (html.equals("0")) {   //no change
    Serial.println("H: No Change!");
  } else {
    lastStatusH = "1";
    Serial.println("H: wifi error, open by default!");
    digitalWrite(H_PIN, HIGH);
  }
  
  delay(30000);
}
