#include "rm67162.h"
#include <TFT_eSPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>

#define SEALEVEL_HPA (1013.25)

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
Adafruit_BME280 bme;

unsigned long delayTime;
u_int count = 0;

void setup()
{  
  rm67162_init();  // amoled lcd initialization
  lcd_setRotation(3);
  sprite.createSprite(536, 240);
  sprite.setSwapBytes(1);

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

void draw()
{
 sprite.fillSprite(TFT_BLACK);
 char x[20];
 sprite.drawString(dtostrf(bme.readTemperature(),6, 2, x),20,20,4);
 sprite.fillRect(10,100,60,60,TFT_RED);
 sprite.fillRect(80,100,60,60,TFT_GREEN);
 sprite.fillRect(150,100,60,60,TFT_BLUE);
 
 lcd_PushColors(0, 0, 536, 240, (uint16_t*)sprite.getPointer());
}


void loop()
{
  if (count == 100)
  {
    printJsonValues();
    count = 0;
  }
  count++;
  draw();
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
  delay(delayTime);
}