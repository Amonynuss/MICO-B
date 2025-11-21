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

    // Calculate the deltas (differences) for Saturation and Value (linear path)
    int satDelta = targetColor.s - currentColor.s;
    int valDelta = targetColor.v - currentColor.v;

    // Calculate the Hue delta for the shortest path
    int hueDelta = targetColor.h - currentColor.h;

    // The short path logic: if the distance is greater than half the circle (128),
    // we take the path in the opposite direction.
    // Hue range is 0-255.
    if (hueDelta > 127)
    {
        hueDelta -= 256; // Forces a negative path (going backwards over the 0 boundary)
    }
    else if (hueDelta < -128)
    {
        hueDelta += 256; // Forces a positive path (going forwards over the 255 boundary)
    }

    for (int i = 0; i <= steps; i++)
    {
        // Add the proportional distance to the start value.
        // Casting the result to (byte) handles the circular overflow (e.g., 250 + 20 = 14) automatically and correctly.
        byte h = currentColor.h + (hueDelta * i / steps);
        byte s = currentColor.s + (satDelta * i / steps);
        byte v = currentColor.v + (valDelta * i / steps);

        FastLED.showColor(CHSV(h, s, v));
        delay(delayTime);
    }

    // Ensure the final color is set exactly
    currentColor = targetColor;
}