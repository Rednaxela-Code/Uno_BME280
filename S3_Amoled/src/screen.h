#include "rm67162.h"
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

void initLCD()
{
  rm67162_init(); // amoled lcd initialization
  lcd_setRotation(3);
  sprite.createSprite(536, 240);
  sprite.setSwapBytes(1);
}

void draw()
{
 sprite.fillSprite(TFT_BLACK);
//  char x[20];
//  char* j = "henk";
//  char* k = dtostrf(bme.readTemperature(),6, 2, x);
//  char* rr = j += k;
//  sprite.drawString(rr ,20,20,4);
 sprite.fillRect(10,100,60,60,TFT_RED);
 sprite.fillRect(80,100,60,60,TFT_GREEN);
 sprite.fillRect(150,100,60,60,TFT_BLUE);
 
 lcd_PushColors(0, 0, 536, 240, (uint16_t*)sprite.getPointer());
}