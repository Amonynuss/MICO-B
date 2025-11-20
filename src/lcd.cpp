#include "lcd.h"

Lcd::Lcd() : tft(TFT_CS, TFT_DC, TFT_RST) {}

void Lcd::begin(void)
{
  if (!Serial) {
    Serial.begin(9600);
    long start = millis();
    while (!Serial && (millis() - start < 3000)); 
  }

  Serial.print(F("Initialize LCD..."));

  tft.initR(INITR_144GREENTAB);

  Serial.println(F("LCD Initialized"));

  tft.fillScreen(ST77XX_BLACK);
  setHeadline("CO2", DataColours::CO2, 0);
  setHeadline("Temperatur", DataColours::TEMP, 1);
  setHeadline("Feuchtigkeit", DataColours::HUMID, 2);
  setHeadline("Druck", DataColours::PRESS, 3);
 
  Serial.println("done");

}

void Lcd::setHeadline(const char *text, uint16_t color, int position)
{
  tft.setTextSize(1);
  tft.setCursor(0, 32 * position);
  tft.setTextColor(color);
  tft.print(text);
}

void Lcd::setData(float data, uint16_t color, int position)
{
  tft.setTextSize(2);
  tft.setCursor(0, 32 * position + 10);
  tft.setTextColor(color);
  tft.print(data);
}

void Lcd::setCo2Level(float level)
{
  setData(level, DataColours::CO2, 0);
}

void Lcd::setTemperature(float temperature)
{
  setData(temperature, DataColours::TEMP, 1);
}

void Lcd::setHumidity(float humidity)
{
  setData(humidity, DataColours::HUMID, 2);
}

void Lcd::setPressure(float pressure)
{
  setData(pressure, DataColours::PRESS, 3);
}
