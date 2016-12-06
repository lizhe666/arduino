#include "Arduino.h"

#include "ESP8266.h"
ESP8266 esp8266;



void setup() {
  Serial.begin(115200);
  Serial.println(((String)"setup in"));


  esp8266.init(&Serial1, 13);
  esp8266.configWithPwd("chuanke-qa", "chuanketest");
  //esp8266.smartConfig("1");
  Serial.println(F("setup out"));
}
//---------------------------------------------------------------------
void loop() {
  byte buf[] = {0x01,0x02,0x03,0x04};
  String host = F("192.168.1.115");
  int port = 8888;
  if(esp8266.tcpStart(host,port)){
    esp8266.tcpSendLength(8);
    esp8266.tcpSend(buf,4);
    esp8266.tcpSend(buf,4);
    esp8266.tcpClose();
  }

  /*
    float t = 24.28;
    float h = 30.28;

    int co2 = 800;
    float hcho = 0.07;

    int pm10 = 10;
    int pm25 = 25;
    int pm100 = 100;



    String host = F("www.ixinfeng.com");
    String path = F("/st/DecisionNewAir?uid=1");
    String data = "?t=" + (String) t + "&h=" + (String) h + "&co2="
                  + (String) co2 + "&hcho=" + (String) hcho + "&pm10=" + (String) pm10
                  + "&pm25=" + (String) pm25 + "&pm100=" + (String) pm100;

    //String html = esp8266.httpGet(host, 8080, path + data);
    String html = esp8266.httpGet(host, 80, path);

    Serial.print(F("html.length="));
    Serial.println(html.length());
    Serial.println(F("__________________"));
    Serial.println(html);
    Serial.println(F("__________________"));

    if(html.equals("2")){
        Serial.println("H");
    }else if(html.equals("1")){
        Serial.println("L");
    }else if(html.equals("0")){
        Serial.println("OFF");
    }
  */
  delay(10000);
  // String d;

}
