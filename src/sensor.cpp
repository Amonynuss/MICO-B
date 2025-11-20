#include <Arduino.h>
#include "sensor.h"


void Sensor::initialize(){
    bmp.begin(0x76);
}

void Sensor::setSeaLevelPressure(float newSeaLevelPressure){
    this->seaLevelPressure = newSeaLevelPressure;
}

void Sensor::printTemperature(){
    Serial.println("Temperatur: " + String(this->getTemperatur()) + "°C");
}

void Sensor::printAltitude(){
    Serial.println("Altitude: " + String(this->getAltitude()) + "m");
}

void Sensor::printPressure(){
    Serial.println("Pressure: " + String(this->getPressure() / 100) + "hPa");
}

float Sensor::getTemperatur(){
    return bmp.readTemperature();
}

float Sensor::getAltitude(){
    return bmp.readAltitude(this->seaLevelPressure);
}

float Sensor::getPressure(){
    return bmp.readPressure();
}

