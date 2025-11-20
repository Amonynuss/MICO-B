#include "lcd.h"

Lcd::Lcd() : tft(TFT_CS, TFT_DC, TFT_RST) {}

void Lcd::initialize(void)
{
  if (!Serial) {
    Serial.begin(9600);
    long start = millis();
    while (!Serial && (millis() - start < 3000)); 
  }

  Serial.println(F("Initialize LCD..."));

  tft.initR(INITR_144GREENTAB);

  Serial.println(F("LCD Initialized!\n"));

  tft.fillScreen(Colours::BACKGROUND);
  setHeadline("CO2", Colours::CO2, 0);
  setCo2Level("-");
  setHeadline("Temperatur", Colours::TEMP, 1);
  setTemperature("-");
  setHeadline("Feuchtigkeit", Colours::HUMID, 2);
  setHumidity("-");
  setHeadline("Druck", Colours::PRESS, 3);  
  setPressure("-");
}

void Lcd::setHeadline(const char *text, uint16_t color, int position)
{
  tft.setTextSize(1);
  tft.setCursor(0, 32 * position);
  tft.setTextColor(color);
  tft.print(text);
}

void Lcd::setData(String data, uint16_t color, int position)
{
  int yPos = 32 * position + 10;

  tft.fillRect(0, yPos, tft.width(), 20, Colours::BACKGROUND); // fill the area with background colour to clear previous data

  tft.setTextSize(2);
  tft.setCursor(0, yPos);
  tft.setTextColor(color);
  tft.print(data);
}

void Lcd::setCo2Level(String level)
{
  setData(level, Colours::CO2, 0);
}

void Lcd::setTemperature(String temperature)
{
  setData(temperature, Colours::TEMP, 1);
}

void Lcd::setHumidity(String humidity)
{
  setData(humidity, Colours::HUMID, 2);
}

void Lcd::setPressure(String pressure)
{
  setData(pressure, Colours::PRESS, 3);
}
