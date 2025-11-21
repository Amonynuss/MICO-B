#include "ampel.h"

void Ampel::initialize()
{
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.clear();
    FastLED.show();
    delay(500);
    setBrightness(150);

    fadeColor(CHSV(PINK.h, PINK.s, 0));
    fadeColor(PINK);
}

void Ampel::setRed()
{
    fadeColor(RED);
}

void Ampel::setOrange()
{
    fadeColor(ORANGE);
}

void Ampel::setGreen()
{
    fadeColor(GREEN);
}

void Ampel::setBrightness(byte newBrightness)
{
    this->brightness = newBrightness;
    FastLED.setBrightness(newBrightness);
}

void Ampel::setCo2Level(String level)
{
    float levelF = level.toFloat();
    if (levelF < 800)
    {
        setGreen();
    }
    else if (levelF >= 800 && levelF < 1200)
    {
        setOrange();
    }
    else
    {
        setRed();
    }
}

void Ampel::fadeColor(CHSV targetColor)
{
    int steps = 50;
    int delayTime = 20;

    int satDelta = targetColor.s - currentColor.s;
    int valDelta = targetColor.v - currentColor.v;

    int hueDelta = targetColor.h - currentColor.h;

    if (hueDelta > 127)
    {
        hueDelta -= 256;
    }
    else if (hueDelta < -128)
    {
        hueDelta += 256;
    }

    for (int i = 0; i <= steps; i++)
    {
        byte h = currentColor.h + (hueDelta * i / steps);
        byte s = currentColor.s + (satDelta * i / steps);
        byte v = currentColor.v + (valDelta * i / steps);

        FastLED.showColor(CHSV(h, s, v));
        delay(delayTime);
    }
    currentColor = targetColor;
}