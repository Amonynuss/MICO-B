#ifndef SENSOR_H
#define SENSOR_H

#include <Adafruit_BMP280.h>
#include <Arduino.h>
#include "bsec.h"
#include <ArduinoJson.h>
#include <sensorData.h>

class Sensor
{
private:
    Bsec iaqSensor;

    const unsigned long interval = 2000;
    unsigned long previousMillis = 0;
    SensorData sensorData;

    void checkIaqSensorStatus();

public:
    void initialize();
    void loop();

    void printTemperature();
    void printHumidity();
    void printPressure();
    void printCO2Level();

    float getTemperatur();
    float getPressure();
    float getHumidity();
    float getCO2Level();

    SensorData getSensorData();
};

#endif