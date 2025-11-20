#include "mqtt.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

Mqtt *Mqtt::instance = nullptr;

Mqtt::Mqtt() : mqttClient(wifiClient)
{
  instance = this;
}

void Mqtt::begin()
{
  if (!Serial)
  {
    Serial.begin(9600);
    long start = millis();
    while (!Serial && (millis() - start < 3000))
      ;
  }

  connectWifi();
  connectMqtt();
  mqttClient.onMessage(handleMessage);
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

void Mqtt::registerCallback(String topic, void (*callback)(String))
{
  this->callback = callback;
  mqttClient.subscribe(baseTopic + topic);
}

void Mqtt::connectWifi()
{
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    Serial.print(".");
    delay(5000);
  }

  Serial.println("\nConnected to the network!");
}

void Mqtt::connectMqtt()
{
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  while (!mqttClient.connected())
  {
    Serial.println("Try MQTT connection ... ");
    mqttClient.connect(broker, port);
  }
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

  callback(message);
}