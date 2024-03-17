#include "Arduino.h"
#include <screen.h>
#include <serial.h>
#include <server.h>

u_int count = 0;

void setup()
{
  initLCD();

  initSerial();
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
