#include "DHT.h"
#define DHTPIN 13     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

#define USE_SERIAL true
#define SWITCH_H_PIN 12

#include <UTFT.h>
extern uint8_t SmallFont[];
UTFT myGLCD(QD220A, A2, A1, A5, A4, A3);

void setup() {
  if (USE_SERIAL) {
    Serial.begin(9600);
    Serial.println("begin!");
  }
  dht.begin();

  pinMode(SWITCH_H_PIN, OUTPUT);
  digitalWrite(SWITCH_H_PIN, LOW);  //close by default

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

}
void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // lcd.setCursor(0, 1);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    if (USE_SERIAL) {
      Serial.println("Failed to read from DHT sensor!");
    }
    digitalWrite(SWITCH_H_PIN, LOW);
    return;
  } else {
    //clear rect last
    // myGLCD.setColor(0, 0, 0);
    // myGLCD.fillRect(129, 46, 179, 146);
    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.print("     ", 130, 46);
    myGLCD.printNumF(t, 2, 130, 46);
    myGLCD.print("     ", 130, 60);
    myGLCD.printNumF(h, 2, 130, 60);


    if (h < 35) {
      digitalWrite(SWITCH_H_PIN, HIGH);
      myGLCD.print("Switch On ", CENTER, 26);

    } else if (h > 40) {
      digitalWrite(SWITCH_H_PIN, LOW);
       myGLCD.print("Switch Off", CENTER, 26);

    }
    if (USE_SERIAL) {
      Serial.print("  Humidity: ");
      Serial.print(h);
      Serial.print(" %\tTemperature: ");
      Serial.print(t);
      Serial.println(" *C ");
    }
    Serial.print("  SWITCH_H_PIN=");
    Serial.println(digitalRead(SWITCH_H_PIN) == 1 ? "On" : "Off");
    Serial.println((millis() / 1000));
  }









}
