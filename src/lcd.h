#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS        10 // Chip Select Pin
#define TFT_RST        8 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         9 // RS Pin on the Board

class Lcd {
    private:
        Adafruit_ST7735 tft;

        enum Colours {
            CO2 = ST77XX_CYAN,
            TEMP = ST77XX_YELLOW,
            HUMID = ST77XX_GREEN,
            PRESS= ST77XX_ORANGE
        };

        void setHeadline(const char* text, uint16_t color, int position);
        void setData(float data, uint16_t color, int position);

    public:
        Lcd();
        void begin();
        void setCo2Level(float level);
        void setTemperature(float temperature);
        void setHumidity(float humidity);
        void setPressure(float pressure);
};

#endif