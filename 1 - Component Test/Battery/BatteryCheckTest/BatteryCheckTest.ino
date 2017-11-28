// for battery check
const int PIN_BAT = A0;
// for 7-SEG LED
#include "SevSeg.h"
SevSeg g_7seg;
const int displayType = COMMON_CATHODE;
const int digit1 = 8;                   //Pin 1
const int digit2 = 5;                   //Pin 10
const int digit3 = 11;                  //Pin 4
const int digit4 = 13;                  //Pin 6
const int segA = 7;                     //Pin 12
const int segB = 6;                     //Pin 11
const int segC = 10;                    //Pin 3
const int segD = 3;                     //Pin 8
const int segE = 9;                     //Pin 2
const int segF = 4;                     //Pin 9
const int segG = 2;                     //Pin 7
const int segDP= 12;                    //Pin 5
const int numberOfDigits = 4;
//
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            A5
#define NUMPIXELS      16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void checkBattery();
void set7Seg(int val);

void setup()
{
  // 7-SEG LED config
  g_7seg.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
  g_7seg.SetBrightness(100);
  //
  pixels.begin();
}

void loop()
{
  checkBattery();
}

void checkBattery()
{
  int val = analogRead(PIN_BAT);
  for(int i=0; i<10; ++i)
  {
    set7Seg(val);
  }
}

void set7Seg(int val)
{
  char str[10];
  sprintf(str, "%4d", val);
  g_7seg.DisplayString(str, 0);
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(0,150,0));
    pixels.show();
  }
}

