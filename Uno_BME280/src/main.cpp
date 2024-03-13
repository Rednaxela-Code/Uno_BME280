#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>

#define SEALEVEL_HPA (1013.25)

Adafruit_BME280 bme;
unsigned long delayTime;

// put function declarations here:
void printValues();
void printJsonValues();

void setup() {
  // put your setup code here, to run once:
  Wire.begin(40);
  Serial.begin(9600);

  bool status;
  status = bme.begin();
  if (!status)
  {
    Serial.println("No BME280 Sensor found!");
    while (1);
  }
  delayTime = 10000;

  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  printJsonValues();
  delay(delayTime);
}

// put function definitions here:
void printValues() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
  
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");
  
  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVEL_HPA));
  Serial.println(" m");
  
  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");
  
  Serial.println();
}

void printJsonValues(){
  StaticJsonDocument<200> doc;

  doc["Temperature"] = bme.readTemperature();
  doc["Humidity"] = bme.readHumidity();
  doc["Pressure"] = bme.readPressure();
  doc["Altitude"] = bme.readAltitude(SEALEVEL_HPA);

  char jsonString[200];
  serializeJson(doc, jsonString);

  Serial.println(jsonString);
}