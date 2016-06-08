#include "Arduino.h"
//#include <MemoryFree.h>

#include <UTFT.h>
// Declare which fonts we will be using
extern uint8_t SmallFont[];
//UTFT myGLCD(Model,SDA,SCL,CS,RST,RS)
//QD220A is for QDtech 2.2inch SPI LCD Module,Driver IC:ILI9225
UTFT myGLCD(QD220A, A2, A1, A5, A4, A3); // Remember to change the model parameter to suit your display module!

int senseAirPin = 10;

#include <Pm25HardSerial.h>
Pm25HardSerial pms5003;

#include "DHT.h"
#define DHTPIN 8     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22
DHT dht(DHTPIN, DHTTYPE);

//定义中断引脚为0，也就是D2引脚
#define INFRA_RED_PIN 2
#define INFRA_RED_INTERRUPT 0

#define USE_WIFI_PIN 7

#include <MD5.h>
#include "ESP8266.h"
ESP8266 esp8266;
//计时器，每分钟才需要上传一次数据，头一分钟后才上传数据
long lastTime = millis();

void setup() {
  Serial.begin(115200);
  pinMode(USE_WIFI_PIN, OUTPUT);

  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);

  // Setup the LCDM
  randomSeed(analogRead(0));
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  // Clear the screen and draw the frame
  myGLCD.clrScr();
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, 219, 13);
  myGLCD.setColor(64, 64, 64);
  myGLCD.fillRect(0, 162, 219, 175);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.print("** Home Sensor Center **", CENTER, 1);
  myGLCD.setBackColor(64, 64, 64);
  myGLCD.setColor(255, 255, 0);
  myGLCD.print("> www.ixinfeng.com <", CENTER, 163);

  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.print("Temperature", 20, 46);
  myGLCD.print("*C", 180, 46);
  myGLCD.print("Humidity", 20, 60);
  myGLCD.print("%", 180, 60);
  myGLCD.print("CO2", 20, 74);
  myGLCD.print("ppm", 180, 74);
  myGLCD.print("HCHO", 20, 88);
  myGLCD.print("mg/L", 180, 88);
  myGLCD.print("PM1.0", 20, 102);
  myGLCD.print("ug/m3", 180, 102);
  myGLCD.print("PM2.5", 20, 116);
  myGLCD.print("ug/m3", 180, 116);
  myGLCD.print("PM10", 20, 130);
  myGLCD.print("ug/m3", 180, 130);

  pinMode(senseAirPin, INPUT);

  pms5003.begin(&Serial2, 9);
  pms5003.sleep(false);

  dht.begin();
  //init sensors end

  if (digitalRead(USE_WIFI_PIN)) { //pin high
    esp8266.init(&Serial1, 13);
    myGLCD.print("Wifi Configing ...", CENTER, 26);
    esp8266.smartConfig();
    //clear last
    myGLCD.print("                  ", CENTER, 26);
    if (esp8266.isWifiConnect()) {
      myGLCD.print("Wifi Connected", CENTER, 26);
    } else {
      myGLCD.print("No Wifi", CENTER, 26);
    }
  } else {
    myGLCD.print("No Wifi", CENTER, 26);
  }

  attachInterrupt(INFRA_RED_INTERRUPT, infraRedLed, CHANGE);

}

void infraRedLed() {
  if (digitalRead(INFRA_RED_PIN)) { //pin high
    digitalWrite(11, HIGH);
  } else {
    digitalWrite(11, LOW);
  }
}

void loop() {
  //Serial.print("freeMemory()=");
  //Serial.println(freeMemory());
  unsigned long duration = pulseIn(senseAirPin, HIGH, 1000);
  int co2 = duration * 5;
  delay(500);

  pms5003.read();
  float hcho = pms5003.getLastHCHO();
  int pm10 = pms5003.getLastPM10();
  int pm25 = pms5003.getLastPM25();
  int pm100 = pms5003.getLastPM100();
  // Reading temperature or humidity takes about 250 milliseconds!
  float h = dht.readHumidity();
  float t = dht.readTemperature();


  //clear rect last
  // myGLCD.setColor(0, 0, 0);
  // myGLCD.fillRect(129, 46, 179, 146);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.print("     ", 130, 46);
  myGLCD.printNumF(t, 2, 130, 46);
  myGLCD.print("     ", 130, 60);
  myGLCD.printNumF(h, 2, 130, 60);
  if (co2 >= 1000) {
    myGLCD.setColor(VGA_YELLOW);
    myGLCD.setBackColor(VGA_RED);
  }
  myGLCD.print("     ", 130, 74);
  myGLCD.printNumI(co2, 130, 74);
  if (co2 >= 1000) {
    myGLCD.setColor(VGA_WHITE);
    myGLCD.setBackColor(VGA_BLACK);
  }

  if (hcho >= 0.08) {
    myGLCD.setColor(VGA_YELLOW);
    myGLCD.setBackColor(VGA_RED);
  }
  myGLCD.print("     ", 130, 88);
  myGLCD.printNumF(hcho, 2, 130, 88);
  if (hcho >= 0.08) {
    myGLCD.setColor(VGA_WHITE);
    myGLCD.setBackColor(VGA_BLACK);
  }

  if (pm25 >= 30) {
    myGLCD.setColor(VGA_YELLOW);
    myGLCD.setBackColor(VGA_RED);
  }
  myGLCD.print("     ", 130, 102);
  myGLCD.printNumI(pm10, 130, 102);
  myGLCD.print("     ", 130, 116);
  myGLCD.printNumI(pm25, 130, 116);
  myGLCD.print("     ", 130, 130);
  myGLCD.printNumI(pm100, 130, 130);
  if (pm25 >= 30) {
    myGLCD.setColor(VGA_WHITE);
    myGLCD.setBackColor(VGA_BLACK);
  }

  if (digitalRead(USE_WIFI_PIN) && millis() - lastTime >= 30000) { //每分钟上传一次数据
    lastTime = millis();

    String host = F("www.ixinfeng.com");
    String path = F("/send");
    String data = "?uid=2&t=" + (String) t + "&h=" + (String) h + "&co2="
                  + (String) co2 + "&hcho=" + (String) hcho + "&pm10="
                  + (String) pm10 + "&pm25=" + (String) pm25 + "&pm100="
                  + (String) pm100;
    //generate the MD5 hash for our string
    char* _data;
    data.toCharArray(_data, data.length() + 1);
    Serial.println(_data[1]);

    unsigned char* hash = MD5::make_hash(_data);
    Serial.println((char*) _data);

    free(_data);
    //generate the digest (hex encoding) of our hash
    char *md5str = MD5::make_digest(hash, 16);
    free(hash);
    //print it on our serial monitor
    Serial.println(md5str);
    data = data + "&sig=" + md5str;
    //Give the Memory back to the System if you run the md5 Hash generation in a loop
    free(md5str);

    Serial.println(data);


    String html = esp8266.httpGet(host, 80, path + data);
    Serial.println(html.length());
    Serial.println(html);

  }

  Serial.println(millis() / 1000);
}

