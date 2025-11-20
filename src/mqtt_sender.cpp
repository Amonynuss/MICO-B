#include "mqtt_sender.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

MqttSender::MqttSender() : mqttClient(wifiClient) {
}

// Neue begin() Methode für Setup-Logik
void MqttSender::begin() {
  if (!Serial) {
    Serial.begin(9600);
    long start = millis();
    while (!Serial && (millis() - start < 3000)); 
  }

  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  
  // WiFi Verbindung
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }

  Serial.println("\nYou're connected to the network");

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
  } else {
    Serial.println("You're connected to the MQTT broker!");
  }
}

void MqttSender::loop() {
  if (!mqttClient.connected()) {
     // Optional: Reconnect Logik hier einfügen oder in begin() auslagern
  }

  mqttClient.poll();

  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    Serial.print("hello ");
    Serial.println(count);

    mqttClient.beginMessage(topic);
    mqttClient.print("hello ");
    mqttClient.print(count);
    mqttClient.endMessage();

    Serial.println();

    count++;
  }
}