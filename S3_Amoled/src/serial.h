#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>

#define SEALEVEL_HPA (1013.25)

Adafruit_BME280 bme;

unsigned long delayTime;

void initSerial()
{
  Wire.setPins(40, 41);
  Serial.begin(9600);
  bool status;
  status = bme.begin();
  if (!status)
  {
    Serial.println("No BME280 Sensor found!");
    while (1)
      ;
  }
}

void printJsonValues()
{
  StaticJsonDocument<200> doc;

  doc["Temperature"] = bme.readTemperature();
  doc["Humidity"] = bme.readHumidity();
  doc["Pressure"] = bme.readPressure();
  doc["Altitude"] = bme.readAltitude(SEALEVEL_HPA);

  char jsonString[200];
  serializeJson(doc, jsonString);

  Serial.println(jsonString);
}