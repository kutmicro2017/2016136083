#include "SevSeg.h"
SevSeg myDisplay;

unsigned long timer;
int deciSecond = 0;

void setup()
{
  int displayType = COMMON_CATHODE;
  int digit1 = 8; //Pin 1
  int digit2 = 5; //Pin 10
  int digit3 = 11; //Pin 4
  int digit4 = 13; //Pin 6
  int segA = 7; //Pin 12
  int segB = 6; //Pin 11
  int segC = 10; //Pin 3
  int segD = 3; //Pin 8
  int segE = 9; //Pin 2
  int segF = 4; //Pin 9
  int segG = 2; //Pin 7
  int segDP= 12; //Pin 5
  int numberOfDigits = 4;
  myDisplay.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
  myDisplay.SetBrightness(100);
  timer = millis();
}

void loop()
{
  char tempString[10]; //Used for sprintf
  sprintf(tempString, "%04d", deciSecond); //Convert deciSecond into a string that is right adjusted
  myDisplay.DisplayString(tempString, 0); //(numberToDisplay, decimal point location)

  //Other examples
  //myDisplay.DisplayString(tempString, 0); //Display string, no decimal point
  //myDisplay.DisplayString("-23b", 3); //Display string, decimal point in third position

  //Check if 10ms has elapsed
  if (millis() - timer >= 100)
  {
    timer = millis();
    deciSecond++;
  }
  delay(5);
}

