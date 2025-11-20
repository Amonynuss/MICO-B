#include <Arduino.h>
#include <ampel.h>
#include <sensor.h>

Ampel ampel;
Sensor sensor;

void setup() {  
  Serial.begin(9600);
  ampel.initialize();
  ampel.setBrightness(200);
  ampel.setRed();

  sensor.initialize();
}

void loop() {
  sensor.printTemperature();
  sensor.printPressure();
  sensor.printAltitude();
  delay(1000);
}