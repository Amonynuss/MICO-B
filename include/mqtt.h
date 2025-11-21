#ifndef MQTT_H
#define MQTT_H

#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "credentials.h"
#include "config.h"
#include "sensorData.h"
#include <ArduinoJson.h>


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
        void onMessage(int messageSize);
        void (*callback)(SensorData message);

        static void handleMessage(int messageSize); 


    public:
        Mqtt();
        
        void initialize();
        void loop();
        void sendMessage(String topic, String message);
        void sendMessage(String topic, SensorData sensorData);
        void registerCallback(String topic, void (*callback)(SensorData));

        String getJsonFromSensorData(SensorData sensorData);
        SensorData getSensorDataFromJson(String json);
};

#endif