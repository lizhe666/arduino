#include "Arduino.h"
//#include <MemoryFree.h>

#include <TFT_HX8357.h> // Hardware-specific library
TFT_HX8357 tft = TFT_HX8357();       // Invoke custom library
#define CENTRE 240
#define TFT_FONT 4

// T6603
//#include <T6603HardSerial.h>
//T6603HardSerial t6603;
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

#include <MD5.h>
#include "ESP8266.h"
ESP8266 esp8266;
#define UPLOAD_INTERVAL 50000
//计时器，每分钟才需要上传一次数据，头一分钟后才上传数据
long lastUploadTime = millis();

void setup() {
  Serial.begin(115200);

  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);

  // Setup the LCDM
  randomSeed(analogRead(0));
  tft.init();
  tft.setRotation(1);
  // Clear the screen and draw the frame
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(0, 0, 480, 27, TFT_RED);
  tft.setTextColor(TFT_WHITE, TFT_RED);
  tft.drawCentreString("** Home Sensor CENTRE **", CENTRE, 1, TFT_FONT);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawCentreString("> www.ixinfeng.com <", CENTRE, 288, TFT_FONT);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("Temperature", 40, 88, TFT_FONT);
  tft.drawRightString("*C", 440, 88, TFT_FONT);
  tft.drawString("Humidity", 40, 116, TFT_FONT);
  tft.drawRightString("%", 440, 116, TFT_FONT);
  tft.drawString("CO2", 40, 144, TFT_FONT);
  tft.drawRightString("ppm", 440, 144, TFT_FONT);
  tft.drawString("HCHO", 40, 172, TFT_FONT);
  tft.drawRightString("mg/L", 440, 172, TFT_FONT);
  tft.drawString("PM1.0", 40, 200, TFT_FONT);
  tft.drawRightString("ug/m3", 440, 200, TFT_FONT);
  tft.drawString("PM2.5", 40, 228, TFT_FONT);
  tft.drawRightString("ug/m3", 440, 228, TFT_FONT);
  tft.drawString("PM10", 40, 256, TFT_FONT);
  tft.drawRightString("ug/m3", 440, 256, TFT_FONT);

  //init sensors begin
  //t6603.begin(&Serial3);
  //t6603.setIdle(false);
  pinMode(senseAirPin, INPUT);
  
  pms5003.begin(&Serial2, 9);
  pms5003.sleep(false);

  dht.begin();
  //init sensors end

  esp8266.init(&Serial1, 13);
  tft.drawCentreString("Wifi Configing ...", CENTRE, 48, TFT_FONT);
  esp8266.smartConfig();
  //clear last
  tft.fillRect(0, 48, 480, 28, TFT_BLACK);
  
  attachInterrupt(INFRA_RED_INTERRUPT, infraRedLed, CHANGE);
}

void infraRedLed() {
  if (digitalRead(INFRA_RED_PIN)) {  //pin high
    digitalWrite(11, HIGH);  //TODO
  } else {
    digitalWrite(11, LOW);
  }
}

int times = 0; //计数器
long co2Avergae = 0;
double hchoAvergae = 0;
long pm10Avergae = 0;
long pm25Avergae = 0;
long pm100Avergae = 0;
double hAvergae = 0;
double tAvergae = 0;

void loop() {
  //Serial.print("freeMemory()=");
  //Serial.println(freeMemory());
  
 /* int co2 = 0;
  if (t6603.getStatus() == 0x00) {
    delay(500);
    co2 = t6603.getCO2();
    Serial.print("co2.getStatus=");
    Serial.println(co2);
  }
  */
  unsigned long duration = pulseIn(senseAirPin, HIGH, 1000);
  int co2 = duration * 2;
  
  delay(500);
  
  pms5003.read();
  float hcho = pms5003.getLastHCHO();
  int pm10 = pms5003.getLastPM10();
  int pm25 = pms5003.getLastPM25();
  int pm100 = pms5003.getLastPM100();
  // Reading temperature or humidity takes about 250 milliseconds!
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (h == NAN) {
    h = hAvergae;
  }
  if (t == NAN) {
    t = tAvergae;
  }
  if (co2 == 0) {
    co2 = co2Avergae;
  }

  //计算平均值
  co2Avergae = (co2Avergae * times + co2) / (times + 1);
  hchoAvergae = (hchoAvergae * times + hcho) / (times + 1);
  pm10Avergae = (pm10Avergae * times + pm10) / (times + 1);
  pm25Avergae = (pm25Avergae * times + pm25) / (times + 1);
  pm100Avergae = (pm100Avergae * times + pm100) / (times + 1);
  hAvergae = (hAvergae * times + h) / (times + 1);
  tAvergae = (tAvergae * times + t) / (times + 1);
  times++;

  

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.fillRect(260, 88, 100, 28, TFT_BLACK);
  tft.drawFloat(t, 2, 260, 88, TFT_FONT);
  tft.fillRect(260, 116, 100, 28, TFT_BLACK);
  tft.drawFloat(h, 2, 260, 116, TFT_FONT);

  if (co2 >= 1000) {
    tft.setTextColor(TFT_RED, TFT_YELLOW);
  }
  tft.fillRect(260, 144, 100, 28, TFT_BLACK);
  tft.drawNumber(co2, 260, 144, TFT_FONT);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  if (hcho >= 0.08) {
    tft.setTextColor(TFT_RED, TFT_YELLOW);
  }
  tft.fillRect(260, 172, 100, 28, TFT_BLACK);
  tft.drawFloat(hcho, 2, 260, 172, TFT_FONT);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  if (pm25 >= 30) {
    tft.setTextColor(TFT_RED, TFT_YELLOW);
  }
  tft.fillRect(260, 200, 100, 28, TFT_BLACK);
  tft.drawNumber(pm10, 260, 200, TFT_FONT);
  tft.fillRect(260, 228, 100, 28, TFT_BLACK);
  tft.drawNumber(pm25, 260, 228, TFT_FONT);
  tft.fillRect(260, 256, 100, 28, TFT_BLACK);
  tft.drawNumber(pm100, 260, 256, TFT_FONT);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  if (esp8266.isWifiConnect()) {
    tft.fillRect(0, 48, 480, 28, TFT_BLACK);
    tft.drawCentreString("Wifi Connected", CENTRE, 48, TFT_FONT);
  } else {
    tft.fillRect(0, 48, 480, 28, TFT_BLACK);
    tft.drawCentreString("No Wifi", CENTRE, 48, TFT_FONT);
  }
  
  if (millis() - lastUploadTime >= UPLOAD_INTERVAL) { //每3分钟上传一次数据
    Serial.println("UPLOAD_INTERVAL");
    Serial.println(millis());
    Serial.println(lastUploadTime);
    Serial.println(millis() - lastUploadTime);
    Serial.println("_______________________________________");

    lastUploadTime = millis();

    String host = F("www.ixinfeng.com");
    String path = F("/send");
    String data = "?uid=1&t=" + (String) tAvergae + "&h="
                  + (String) hAvergae + "&co2=" + (String) co2Avergae + "&hcho="
                  + (String) hchoAvergae + "&pm10=" + (String) pm10Avergae
                  + "&pm25=" + (String) pm25Avergae + "&pm100="
                  + (String) pm100Avergae;
    String sigData = data + "2054120bd4cb83bb";
    //generate the MD5 hash for our string
    char* _data;
    sigData.toCharArray(_data, sigData.length() + 1);
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
    

    times = 0; //充值平均值计数器
    co2Avergae = 0;
    hchoAvergae = 0;
    pm10Avergae = 0;
    pm25Avergae = 0;
    pm100Avergae = 0;
    hAvergae = 0;
    tAvergae = 0;
  } else {
    Serial.println("UPLOAD_INTERVAL__NOT_IN");
    Serial.println(millis());
    Serial.println(lastUploadTime);
    Serial.println(millis() - lastUploadTime);
    Serial.println("_______________________________________");

  }

  Serial.println(millis() / 1000);
}

