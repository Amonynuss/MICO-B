#include <Arduino.h>
#include <ampel.h>
#include <sensor.h>
#include <mqtt.h>
#include <lcd.h>
#include "startup.h"
#include <functional>

#define RECEIVER

Startup startup;
Ampel ampel;
Sensor sensor;
Mqtt mqtt;
Lcd lcd;

void test(String message) {
  Serial.print("Callback executed with message: ");
  Serial.println(message);
}

void setup() {
  Serial.begin(9600);
  while(!Serial){}
  startup.printBootArt();
  mqtt.begin();

  #ifdef TRANSMITTER
  // The following setup code is for the transmitter
  startup.printTransmitterArt();
  sensor.initialize();
  mqtt.registerCallback("receiver", test);
  #endif


  #ifdef RECEIVER
  // The following setup code is for the receiver
  startup.printReceiverArt();
  // Register member function using std::bind (std::function accepted by Mqtt)
  mqtt.registerCallback("transmitter", std::bind(&Lcd::setCo2Level, &lcd, std::placeholders::_1));

  lcd.begin();
  // ampel.initialize();
  // ampel.setBrightness(200);
  // ampel.setRed();
  #endif

  


  lcd.begin();
  lcd.setCo2Level(String(450.0));
  lcd.setTemperature(String(22.5));
  lcd.setHumidity(String(45.0));
  lcd.setPressure(String(1013.25));
  
}

void loop() {
  mqtt.loop();

  #ifdef TRANSMITTER
  // The following loop code is for the transmitter
  // sensor.loop();

  mqtt.sendMessage("transmitter", String(sensor.getCO2Level()));
  delay(1000);
  #endif


  #ifdef RECEIVER
  // The following loop code is for the receiver
  #endif
}