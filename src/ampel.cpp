#include "ampel.h"

void Ampel::initialize(){
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  setBrightness(150);
}

void Ampel::setRed(){
    this->color = RED;
    FastLED.showColor(CRGB::Red);
}

void Ampel::setOrange(){
    this->color = ORANGE;
    FastLED.showColor(CRGB::Orange);
}

void Ampel::setGreen(){
    this->color = GREEN;
    FastLED.showColor(CRGB::Green);
}

AmpelColor Ampel::getColor(){
    return this-> color;
}

void Ampel::setBrightness(byte newBrightness){
    this->brightness = newBrightness;
    FastLED.setBrightness(newBrightness);
}

void Ampel::setCo2Level(String level)
{
    float levelF = level.toFloat();
    if(levelF < 800){
        setGreen();
    } else if(levelF >= 800 && levelF < 1200){
        setOrange();
    } else {
        setRed();
    }
}

byte Ampel::getBrightness(){
    return this->brightness;
}