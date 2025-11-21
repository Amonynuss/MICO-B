#ifndef MQTT_H
#define MQTT_H

#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

class Mqtt {

    private:
        WiFiClient wifiClient;
        MqttClient mqttClient;

        const char* broker = "192.168.37.4";
        int port = 1883;
        const char* baseTopic  = "micob/ampel/";

        const unsigned long interval = 1000;
        unsigned long previousMillis = 0;

        int count = 0;

        void connectWifi();
        void connectMqtt();

    public:
        Mqtt();
        void begin();
        void loop();

        void sendMessage(const char* topic, const char* message);
};

#endif