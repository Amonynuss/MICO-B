#include <Arduino.h>
#include <ampel.h>
#include <sensor.h>
#include <mqtt_sender.h>
#include "startup.h"

Startup startup;
Ampel ampel;
Sensor sensor;
MqttSender mqttSender;

void setup() {  
  Serial.begin(9600);
  while(!Serial){}
  startup.printBootArt();
  ampel.initialize();
  ampel.setBrightness(200);
  ampel.setRed();

  sensor.initialize();
  mqttSender.begin();
}

void loop() {
  sensor.loop();
  mqttSender.loop();
}