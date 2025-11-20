#ifndef MQTT_H
#define MQTT_H

#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "credentials.h"
#include "config.h"

class Mqtt {

    private:
        WiFiClient wifiClient;
        MqttClient mqttClient;

        const char* broker = MQTT_SERVER_IP;
        int port = MQTT_PORT;
        const char* baseTopic  = MQTT_BASE_TOPIC;

        const unsigned long interval = 1000;
        unsigned long previousMillis = 0;

        int count = 0;

        void connectWifi();
        void connectMqtt();
        static void onMqttMessage(int messageSize);

    public:
        Mqtt();
        void begin();
        void loop();

        void sendMessage(const char* topic, const char* message);
};

#endif