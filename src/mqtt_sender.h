#ifndef MQTTSENDER_H
#define MQTTSENDER_H

#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

class MqttSender {

    private:
        WiFiClient wifiClient;
        MqttClient mqttClient;

        const char* broker = "test.mosquitto.org";
        int port = 1883;
        const char* topic  = "arduino/simple";

        const unsigned long interval = 1000;
        unsigned long previousMillis = 0;

        int count = 0;

    public:
        MqttSender();
        void begin();
        void loop();

};

#endif