#include "mqtt.h"
#include <sensorData.h>
#include <ArduinoJson.h>

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

Mqtt *Mqtt::instance = nullptr;

Mqtt::Mqtt() : mqttClient(wifiClient)
{
  instance = this;
}

void Mqtt::initialize()
{
  connectWifi();
  connectMqtt();
  mqttClient.onMessage(handleMessage);
  Serial.print("\n\n\n");
}

void Mqtt::loop()
{
  if (!mqttClient.connected())
  {
    connectMqtt();
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    connectWifi();
  }

  mqttClient.poll();
}

void Mqtt::sendMessage(String topic, String message)
{
  String fullTopic = baseTopic + topic;

  Serial.print("Sending message to topic: ");
  Serial.println(fullTopic);
  Serial.println(message);
  Serial.println();

  mqttClient.beginMessage(fullTopic);
  mqttClient.print(message);
  mqttClient.endMessage();
}

void Mqtt::sendMessage(String topic, SensorData sensorData)
{
  String message = this->getJsonFromSensorData(sensorData);
  this->sendMessage(topic, message);
}

String Mqtt::getJsonFromSensorData(SensorData sensorData)
{
  JsonDocument doc;

  doc["temperature"] = sensorData.temperature;
  doc["humidity"] = sensorData.humidity;
  doc["pressure"] = sensorData.pressure;
  doc["co2"] = sensorData.co2;

  String jsonString;
  serializeJson(doc, jsonString);

  return jsonString;
}

SensorData Mqtt::getSensorDataFromJson(String json)
{

  JsonDocument receivedData;
  SensorData sensorData;
  deserializeJson(receivedData, json);
  String co2 = receivedData["co2"];
  String temperature = receivedData["temperature"];
  String humidity = receivedData["humidity"];
  String pressure = receivedData["pressure"];

  sensorData.co2 = co2;
  sensorData.temperature = temperature;
  sensorData.humidity = humidity;
  sensorData.pressure = pressure;

  return sensorData;
}

void Mqtt::registerCallback(String topic, void (*callback)(SensorData))
{
  this->callback = callback;
  mqttClient.subscribe(baseTopic + topic);
}

void Mqtt::connectWifi()
{
  Serial.println("Connecting to the network...");

  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    delay(5000);
  }

  Serial.println("Successfully connected to the network!\n");
  delay(500);
}

void Mqtt::connectMqtt()
{
  Serial.println("Connecting to the mqtt broker...");

  while (!mqttClient.connected())
  {
    mqttClient.connect(broker, port);
  }
  Serial.println("Successfully connected to mqtt broker!");
}

void Mqtt::handleMessage(int messageSize)
{
  if (instance)
  {
    instance->onMessage(messageSize);
  }
}

void Mqtt::onMessage(int messageSize)
{
  Serial.print("Received message");
  String topic = mqttClient.messageTopic();
  Serial.print("Topic: ");
  Serial.println(topic);
  String message;
  while (mqttClient.available())
  {
    char c = mqttClient.read();
    message += c;
  }
  Serial.print("Message: ");
  Serial.println(message);
  Serial.println();

  SensorData data = this->getSensorDataFromJson(message);

  if (callback)
  {
    callback(data);
  }
}