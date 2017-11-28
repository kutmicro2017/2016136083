// for temp sensor
#include <math.h>
const int B = 4275;
const int R0 = 100000;
const int PIN_TEMP = A5;
// for RGB LED
const int PIN_RED = 2;
const int PIN_GREEN = 3;
const int PIN_BLUE = 4;
// for NeoPixel
#include <Adafruit_NeoPixel.h>
const int PIN_NEO = 5;
const int NUM_PIXELS = 16;
Adafruit_NeoPixel g_pixels = Adafruit_NeoPixel(NUM_PIXELS, PIN_NEO, NEO_GRB + NEO_KHZ800);
int g_num = 1;
// for touch sensor
const int PIN_TOUCH = 6;
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

void printTemp();
void setRgbLed(int red, int green, int blue);
void setNeoPixel(int red, int green, int blue, int num);
void printTouch();
void printBattery();
void set7Seg(int val);

void setup()
{
  // serial moniter config
  Serial.begin(9600);
  // RGB LED pin config
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  // NeoPixel config
  g_pixels.begin();
  // touch sensor pin config
  pinMode(PIN_TOUCH, INPUT);
  // 7-SEG LED config
  g_7seg.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
  g_7seg.SetBrightness(100);
}

void loop()
{
  printTemp();
  setNeoPixel(255, 255, 255, g_num);
  printTouch();
  printBattery();
  delay(100);
  if(g_num == 16)
  {
    g_num = 1;
  }
  else
  {
    ++g_num;
  }
  Serial.print("--------------------\n");
}

void printTemp()
{
  int a = analogRead(PIN_TEMP);
  float R = (1023.0f / a) - 1.0f;
  R = R * R0;
  float temp = 1.0f / (log(R/R0)/B + 1/298.15) - 273.15;
  Serial.print("\t temp = ");
  Serial.println(temp);
}

void setRgbLed(int red, int green, int blue)
{
  analogWrite(PIN_RED, red);
  analogWrite(PIN_GREEN, green);
  analogWrite(PIN_BLUE, blue);
}

void setNeoPixel(int red, int green, int blue, int num)
{
  for(int i=0; i<NUM_PIXELS; ++i)
  {
    g_pixels.setPixelColor(i, g_pixels.Color(0, 0, 0));
  }
  g_pixels.show();
  for(int i=0; i<num; ++i)
  {
    g_pixels.setPixelColor(i, g_pixels.Color(red, green, blue));
  }
  g_pixels.show();
}

void printTouch()
{
  int val = digitalRead(PIN_TOUCH);
  if(val == HIGH)
  {
    Serial.println("\t touched");
  }
  else
  {
    Serial.println("\t not touched");
  }
}

void printBattery()
{
  int val = analogRead(PIN_BAT);
  float output = (float(val)*5) / 1023 * 2;

  Serial.print("\t Analog val = ");
  Serial.println(val);
  Serial.print("\t voltage = ");
  Serial.println(output);

  if(output > 4.3)
  {
    setRgbLed(0, 255, 0);
  }
  else if(output > 4.1)
  {
    setRgbLed(128, 64, 0);
  }
  else
  {
    setRgbLed(255, 0, 0);
  }
  set7Seg(val);
}

void set7Seg(int val)
{
  char str[10];
  sprintf(str, "%4d", 1111);
  g_7seg.DisplayString(str, 0);
  delay(5);
}

