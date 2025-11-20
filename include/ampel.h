#ifndef AMPEL_H
#define AMPEL_H

#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN     12      // Data pin connected to the strip
#define NUM_LEDS    8       // Number of LEDs in the strip
#define LED_TYPE    WS2812B // Type of LED chip
#define COLOR_ORDER GRB     // Color order

enum AmpelColor {
  RED,
  ORANGE,
  GREEN
};


class Ampel{
    private:
        AmpelColor color;
        CRGB leds[NUM_LEDS];
        byte brightness;

    public:
        void initialize();
        void setRed();
        void setOrange();
        void setGreen();
        void setBrightness(byte newBrightness);

        void setCo2Level(String level);

        AmpelColor getColor();
        byte getBrightness();
};

#endif