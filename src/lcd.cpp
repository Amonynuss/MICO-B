#include "lcd.h"

Lcd::Lcd() : tft(TFT_CS, TFT_DC, TFT_RST) {}

void Lcd::initialize(void)
{
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

void Lcd::setData(String data, String unit, uint16_t color, int position)
{
  int yPos = 32 * position + 10;

  tft.fillRect(0, yPos, tft.width(), 20, Colours::BACKGROUND); // fill the area with background colour to clear previous data

  tft.setTextSize(2);
  tft.setCursor(0, yPos);
  tft.setTextColor(color);
  tft.print(data);
  tft.setTextSize(1);
  tft.print(" ");
  tft.print(unit);
}

void Lcd::setCo2Level(String level)
{
  if(level != oldCo2Level)
  {
    setData(level, "ppM", Colours::CO2, 0);
    oldCo2Level = level;
  }
}

void Lcd::setTemperature(String temperature)
{
  if(temperature != oldTemperature)
  {
    setData(temperature, "C", Colours::TEMP, 1);
    oldTemperature = temperature;
  }
}

void Lcd::setHumidity(String humidity)
{
  if(humidity != oldHumidity)
  {
    setData(humidity, "%", Colours::HUMID, 2);
    oldHumidity = humidity;
  }
}

void Lcd::setPressure(String pressure)
{
  if(pressure != oldPressure)
  {
    setData(pressure, "hPa", Colours::PRESS, 3);
    oldPressure = pressure;
  }
}

void Lcd::showData(SensorData sensorData)
{
  this->setCo2Level(sensorData.co2);
  this->setHumidity(sensorData.humidity);
  this->setTemperature(sensorData.temperature);
  this->setPressure(sensorData.pressure);
}
