#ifndef SENSOR_H
#define SENSOR_H

#include <Adafruit_BMP280.h>
#include <Arduino.h>
#include "bsec.h"


class Sensor{
    private:
        Bsec iaqSensor;

        const unsigned long interval = 2000;
        unsigned long previousMillis = 0;

        void checkIaqSensorStatus();

    public:
        void initialize();
        void loop();

        void printTemperature();
        void printHumidity();
        void printPressure();
        void printCO2Level();
        void printBreathVoc();

        void printRawTemperature();
        void printRawHumidity();

        float getTemperatur();
        float getPressure();
        float getHumidity();
        float getCO2Level();
        float getBreathVoc();

        float getRawTemperatur();
        float getRawHumidity();
};

#endif