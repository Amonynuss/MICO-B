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

void setup() {  
  Serial.begin(9600);
  while(!Serial){}
  startup.printBootArt();

  // ampel.initialize();
  // ampel.setBrightness(200);
  // ampel.setRed();

  // sensor.initialize();

  mqtt.begin();

  lcd.begin();
  lcd.setCo2Level(450.0);
  lcd.setTemperature(22.5);
  lcd.setHumidity(45.0);
  lcd.setPressure(1013.25);
}

void loop() {
  #ifdef TRANSMITTER
  // The following code is for the transmitter
  sensor.loop();
  mqtt.loop();
  #endif


  #ifdef RECEIVER
  // The following code is for the receiver
  #endif
}