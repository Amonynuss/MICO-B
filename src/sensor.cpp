#include <Arduino.h>
#include "sensor.h"
#include <ArduinoJson.h>
#include <sensorData.h>


void Sensor::initialize(){
    bsec_virtual_sensor_t sensorList[13] = {
            BSEC_OUTPUT_IAQ,
            BSEC_OUTPUT_STATIC_IAQ,
            BSEC_OUTPUT_CO2_EQUIVALENT,
            BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
            BSEC_OUTPUT_RAW_TEMPERATURE,
            BSEC_OUTPUT_RAW_PRESSURE,
            BSEC_OUTPUT_RAW_HUMIDITY,
            BSEC_OUTPUT_RAW_GAS,
            BSEC_OUTPUT_STABILIZATION_STATUS,
            BSEC_OUTPUT_RUN_IN_STATUS,
            BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
            BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
            BSEC_OUTPUT_GAS_PERCENTAGE
        };
    

    iaqSensor.begin(BME68X_I2C_ADDR_LOW, Wire);
    this->checkIaqSensorStatus();
    iaqSensor.updateSubscription(sensorList, 13, BSEC_SAMPLE_RATE_LP);
    this->checkIaqSensorStatus();
}

void Sensor::loop(){
    if (millis() - previousMillis >= interval) {
        previousMillis = millis();
        if (iaqSensor.run()) {
            // this->getCO2Level();
            // this->getHumidity();
            // this->getPressure();
            // this->getTemperatur();

            // this->printCO2Level();
            // this->printHumidity();
            // this->printPressure();
            // this->printTemperature();
            // this->printJson();
        }
    }
}

void Sensor::printTemperature(){
    Serial.println("Temperatur: " + String(this->getTemperatur()) + "°C");
}

void Sensor::printCO2Level(){
    Serial.println("CO2 Level: "+ String(this->getCO2Level()));
}

void Sensor::printPressure(){
    Serial.println("Pressure: " + String(this->getPressure() / 100) + "hPa");
}

void Sensor::printHumidity(){
    Serial.println("Humidity: " + String(this->getHumidity()) + "%");
}

float Sensor::getTemperatur(){
    return round(iaqSensor.temperature * 100) / 100.;
}

float Sensor::getPressure(){
    return round(iaqSensor.pressure) / 100.;
}

float Sensor::getHumidity(){
    return round(iaqSensor.humidity * 100) / 100.;
}

float Sensor::getCO2Level(){
    return round(iaqSensor.co2Equivalent * 100) / 100.;
}

void Sensor::checkIaqSensorStatus(){
    String output;
    if (iaqSensor.bsecStatus != BSEC_OK) {
        if (iaqSensor.bsecStatus < BSEC_OK) {
            output = "BSEC error code : " + String(iaqSensor.bsecStatus);
            Serial.println(output);
        } else {
            output = "BSEC warning code : " + String(iaqSensor.bsecStatus);
            Serial.println(output);
        }
    }

    if (iaqSensor.bme68xStatus != BME68X_OK) {
        if (iaqSensor.bme68xStatus < BME68X_OK) {
            output = "BME68X error code : " + String(iaqSensor.bme68xStatus);
            Serial.println(output);
        } else {
            output = "BME68X warning code : " + String(iaqSensor.bme68xStatus);
            Serial.println(output);
        }
    }
}

String Sensor::getDataAsJson(){
    JsonDocument doc;
    
    doc["temperature"] = this->getTemperatur();
    doc["humidity"] = this->getHumidity();
    doc["pressure"] = this->getPressure();
    doc["co2"] = this->getCO2Level();
    
    String jsonString;
    serializeJson(doc, jsonString);
    
    return jsonString;
}

void Sensor::printJson(){
    Serial.println("JSON: " + this->getDataAsJson());
}

SensorData Sensor::getSensorData(){
    this->sensorData.temperature    = String(this->getTemperatur());
    this->sensorData.humidity       = String(this->getHumidity());
    this->sensorData.pressure       = String(this->getPressure());
    this->sensorData.co2            = String(this ->getCO2Level());

    return this->sensorData;
}