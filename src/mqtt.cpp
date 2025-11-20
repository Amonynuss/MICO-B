#include "mqtt.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

Mqtt::Mqtt() : mqttClient(wifiClient)
{
}

void Mqtt::begin()
{
  if (!Serial) {
    Serial.begin(9600);
    long start = millis();
    while (!Serial && (millis() - start < 3000)); 
  }
  
  connectWifi();
  connectMqtt();

  mqttClient.onMessage(onMqttMessage);
}

void Mqtt::loop()
{
  if (!mqttClient.connected()) {
     connectMqtt();
  }
  if(WiFi.status() != WL_CONNECTED) {
    connectWifi();
  }

  mqttClient.poll();

  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    sendMessage("test", "hello");

    Serial.println();

    count++;
  }
}

void Mqtt::sendMessage(const char *topic, const char *message)
{
  String fullTopic = String(baseTopic) + String(topic);

  Serial.print("Sending message to topic: ");
  Serial.println(fullTopic);
  Serial.println(message);
  Serial.println();

  mqttClient.beginMessage(fullTopic);
  mqttClient.print(message);
  mqttClient.endMessage();
}

void Mqtt::connectWifi()
{
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }

  Serial.println("\nConnected to the network!");
}

void Mqtt::connectMqtt()
{
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
  } else {
    Serial.println("Connected to the MQTT broker!");
  }
}

void Mqtt::onMqttMessage(int messageSize)
{
  
}
