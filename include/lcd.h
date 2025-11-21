#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <sensorData.h>

#define TFT_CS 10 // Chip Select Pin
#define TFT_RST 8 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 9  // RS Pin on the Board

class Lcd
{
private:
    Adafruit_ST7735 tft;

    enum Mode
    {
        STARTUP,
        CONNECT_MQTT,
        DISPLAY_DATA
    };
    uint8_t mode = STARTUP;

    enum Colours
    {
        BACKGROUND = ST77XX_BLACK,
        CO2 = ST77XX_CYAN,
        TEMP = ST77XX_YELLOW,
        HUMID = ST77XX_GREEN,
        PRESS = ST77XX_ORANGE
    };

    String oldCo2Level = "";
    String oldTemperature = "";
    String oldHumidity = "";
    String oldPressure = "";

    void setHeadline(const char *text, uint16_t color, int position);
    void setData(String data, String unit, uint16_t color, int position);

public:
    Lcd();
    void initialize();

    void setCo2Level(String level);
    void setTemperature(String temperature);
    void setHumidity(String humidity);
    void setPressure(String pressure);
    void showData(SensorData sensorData);
};

#endif