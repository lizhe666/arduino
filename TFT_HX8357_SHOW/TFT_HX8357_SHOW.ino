#include "Arduino.h"

// Delay between demo pages
#define CENTRE 240
#include <TFT_HX8357.h> // Hardware-specific library
TFT_HX8357 tft = TFT_HX8357();       // Invoke custom library
#define TFT_GREY 0x7BEF

void setup()
{
  randomSeed(analogRead(0));
  Serial.begin(38400);
  // Setup the LCD
  tft.init();
  tft.setRotation(1);
}

void loop()
{
  tft.fillScreen(TFT_BLACK);

  tft.fillRect(0, 305, 480, 320, TFT_GREY);
  tft.setTextColor(TFT_BLACK, TFT_RED);

  tft.drawCentreString("* TFT_HX8357 *", CENTRE, 3, 1);
  tft.setTextColor(TFT_YELLOW, TFT_GREY);
  tft.drawCentreString("Adapted by Bodmer", CENTRE, 309, 1);


}

