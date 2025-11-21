#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <Arduino.h>

struct SensorData
{
    String temperature;
    String humidity;
    String pressure;
    String co2;
};

#endif