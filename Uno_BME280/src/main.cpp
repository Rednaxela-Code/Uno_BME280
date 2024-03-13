#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h>

#define SEALEVEL_HPA (1013.25)
#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5

Adafruit_BME280 bme;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int lcdKey = 0;
int adcKeyIn = 0;
unsigned long delayTime;


// put function declarations here:
void printValues();
void printJsonValues();
void loopLCD();
int readLCDButtons();

void setup()
{
  // put your setup code here, to run once:
  Wire.begin(40);
  Serial.begin(9600);

  lcd.begin(16, 2);

  bool status;
  status = bme.begin();
  if (!status)
  {
    Serial.println("No BME280 Sensor found!");
    while (1)
      ;
  }
  delayTime = 10000;

  Serial.println();
}

void loop()
{
  // put your main code here, to run repeatedly:
  //printJsonValues();
  loopLCD();
}

// put function definitions here:
void printValues()
{
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

  delay(delayTime);
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

int readLCDButtons()
{
  adcKeyIn = analogRead(0); // read the value from the sensor
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  // We make this the 1st option for speed reasons since it will be the most likely result
  if (adcKeyIn > 1000)
    return btnNONE;
  // For V1.1 us this threshold
  if (adcKeyIn < 50)
    return btnRIGHT;
  if (adcKeyIn < 250)
    return btnUP;
  if (adcKeyIn < 450)
    return btnDOWN;
  if (adcKeyIn < 650)
    return btnLEFT;
  if (adcKeyIn < 850)
    return btnSELECT;
  // For V1.0 comment the other threshold and use the one below:
  /*
  if (adc_key_in < 50) return btnRIGHT;
  if (adc_key_in < 195) return btnUP;
  if (adc_key_in < 380) return btnDOWN;
  if (adc_key_in < 555) return btnLEFT;
  if (adc_key_in < 790) return btnSELECT;
  */
  return btnNONE; // when all others fail, return this...
}

void loopLCD()
{
  lcd.setCursor(0, 0);
  String humText = "Hum hPa: ";
  lcd.print(humText += bme.readHumidity());
  lcd.setCursor(9, 1);         // move cursor to second line "1" and 9 spaces over

  lcd.setCursor(0, 1);         // move to the begining of the second line
  lcdKey = readLCDButtons(); // read the buttons

  String tempText = "Temp  C: ";
   lcd.print(tempText += bme.readTemperature());
}