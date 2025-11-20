#include <Arduino.h>
#include <ampel.h>
#include <sensor.h>
#include <mqtt.h>
#include <lcd.h>
#include "startup.h"

#define TRANSMITTER

Startup startup;
Ampel ampel;
Sensor sensor;
Mqtt mqtt;
Lcd lcd;

void test(String message) {
  Serial.print("Callback executed with message: ");
  Serial.println(message);
}

void jsonTest(String message) {
  JsonDocument receivedData;
  deserializeJson(receivedData, message);
  lcd.setCo2Level((receivedData["co2"]));
  lcd.setTemperature((receivedData["temperature"]));
  lcd.setHumidity((receivedData["humidity"]));
  lcd.setPressure((receivedData["pressure"]));
}

void setup() {
  Serial.begin(9600);
  while(!Serial){}
  startup.printBootArt();

  #ifdef TRANSMITTER
  // The following setup code is for the transmitter
  startup.printTransmitterArt();
  sensor.initialize();
  mqtt.initialize();
  mqtt.registerCallback("receiver", test);
  #endif


  #ifdef RECEIVER
  // The following setup code is for the receiver

  startup.printReceiverArt();
  // Register member function using std::bind (std::function accepted by Mqtt)
  mqtt.initialize();
  mqtt.registerCallback("transmitter", std::bind(&Lcd::setCo2Level, &lcd, std::placeholders::_1));

  lcd.initialize();
  // ampel.initialize();
  // ampel.setBrightness(200);
  // ampel.setRed();
  lcd.begin();
  ampel.initialize();
  ampel.setRed();

  mqtt.begin();
  mqtt.registerCallback("transmitter", jsonTest);

  ampel.setOrange();

  #endif
}

void loop() {
  mqtt.loop();

  #ifdef TRANSMITTER
  // The following loop code is for the transmitter
  sensor.loop();
  mqtt.sendMessage("transmitter", sensor.getDataAsJson());

  sensor.loop();

  mqtt.sendMessage("transmitter", String(sensor.getCO2Level()));
  delay(1000);
  #endif


  #ifdef RECEIVER
  // The following loop code is for the receiver

  // mqtt.sendMessage("receiver", "Hello from Receiver");
  // delay(1000);
  #endif
}