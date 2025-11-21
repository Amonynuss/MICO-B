#ifndef AMPEL_H
#define AMPEL_H

#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN 12       // Data pin connected to the strip
#define NUM_LEDS 8       // Number of LEDs in the strip
#define LED_TYPE WS2812B // Type of LED chip
#define COLOR_ORDER GRB  // Color order

class Ampel
{
private:
  const CHSV RED = CHSV(0, 255, 255);
  const CHSV ORANGE = CHSV(16, 255, 255);
  const CHSV GREEN = CHSV(96, 255, 255);
  const CHSV BLUE = CHSV(160, 255, 255);
  const CHSV PINK = CHSV(200, 255, 255);

  CRGB leds[NUM_LEDS];
  CHSV currentColor;
  byte brightness;

  void fadeColor(CHSV targetColor);

public:
  void initialize();
  void setRed();
  void setOrange();
  void setGreen();
  void setBrightness(byte newBrightness);

  void setCo2Level(String level);
};

#endif