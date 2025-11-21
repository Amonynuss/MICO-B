#include <Arduino.h>
#include <ampel.h>
#include <sensor.h>
#include <mqtt.h>
#include <lcd.h>
#include <startup.h>

#define RECEIVER

Startup startup;
Ampel ampel;
Sensor sensor;
Mqtt mqtt;
Lcd lcd;

void showData(SensorData data) {
  lcd.showData(data);
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
  #endif


  #ifdef RECEIVER
  // The following setup code is for the receiver

  startup.printReceiverArt();

  lcd.initialize();
  ampel.initialize();
  ampel.setRed();

  mqtt.initialize();
  mqtt.registerCallback("transmitter", showData);

  ampel.setOrange();

  #endif
}

void loop() {
  mqtt.loop();

  #ifdef TRANSMITTER
  // The following loop code is for the transmitter
  sensor.loop();
  mqtt.sendMessage("transmitter", sensor.getSensorData());
  delay(1000);
  #endif


  #ifdef RECEIVER
  // The following loop code is for the receiver

  // mqtt.sendMessage("receiver", "Hello from Receiver");
  // delay(1000);
  #endif
}