#ifndef SENSOR_H
#define SENSOR_H

#include <Adafruit_BMP280.h>
#include <Arduino.h>


class Sensor{
    private:
        Adafruit_BMP280 bmp;
        float seaLevelPressure = 1013.25;

        const unsigned long interval = 2000;
        unsigned long previousMillis = 0;

    public:
        void initialize();
        void loop();

        void setSeaLevelPressure(float newSeaLevelPressure);
        void printTemperature();
        void printAltitude();
        void printPressure();

        float getTemperatur();
        float getAltitude();
        float getPressure();
};

#endif