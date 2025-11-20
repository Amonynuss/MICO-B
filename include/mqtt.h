#ifndef MQTT_H
#define MQTT_H

#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "credentials.h"
#include "config.h"
#include <functional>

class Mqtt {

    private:
        static Mqtt* instance;

        WiFiClient wifiClient;
        MqttClient mqttClient;

        const char* broker = MQTT_SERVER_IP;
        int port = MQTT_PORT;
        String baseTopic  = MQTT_BASE_TOPIC;

        void connectWifi();
        void connectMqtt();
        static void handleMessage(int messageSize); 
        void onMessage(int messageSize);

        std::function<void(String)> callback;

    public:
        Mqtt();
        void initialize();
        void loop();

        void sendMessage(String topic, String message);
        void registerCallback(String topic, std::function<void(String)> callback);
};

#endif