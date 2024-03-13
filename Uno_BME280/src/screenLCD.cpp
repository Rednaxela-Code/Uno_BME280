#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal.h>

#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int lcdKey = 0;
int adcKeyIn = 0;

void loopLCD();
int readLCDButtons();

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

  return btnNONE; // when all others fail, return this...
}

void loopLCD(Adafruit_BME280 bme)
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