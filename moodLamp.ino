#include <Adafruit_NeoPixel.h>
#include <math.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define _DEBUG

enum eColor { RED_TO_BLUE, ORANGE_TO_PURPLE, YELLOW_TO_CYAN };

#define NEO_PIXEL 4
#define COLOR_BUTTON 2
#define BRIGHTNESS_BUTTON 3
#define TEMP_SENSOR A5
#define BATTERY A0
#define RGB_RED 5
#define RGB_GREEN 6
#define RGB_BLUE 7

#define LOWEST_TEMPERATURE 0
#define NORMAL_TEMPERATURE 15
#define HIGHEST_TEMPERATURE 30
const int NORMAL_TEMPERATURE_VARIABLE = NORMAL_TEMPERATURE * 10;
const int THERMISTER = 4275;
const int R0 = 100000; // 100kelvin

volatile int gBrightness = 2;
volatile int gColor = eColor::RED_TO_BLUE;
volatile bool gbIsBrightnessChanged = false;
Adafruit_NeoPixel gCirclePixel = Adafruit_NeoPixel(16, NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void ChangeColor();
void ChangeBrightness();

struct RGB
{
  int R;
  int G;
  int B;
};

void setup()
{
#ifdef __AVR_ATtiny85__
  if (F_CPU) == 16000000)
  {
    clock_prescale_set(clock_div_1); 
  }
#endif
  gCirclePixel.begin();
  gCirclePixel.show();

  pinMode(COLOR_BUTTON, INPUT_PULLUP);
  pinMode(BRIGHTNESS_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(COLOR_BUTTON), ChangeColor, FALLING);
  attachInterrupt(digitalPinToInterrupt(BRIGHTNESS_BUTTON), ChangeBrightness, FALLING); 

  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_GREEN, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  //To calculate the temperature
  int analogVal = analogRead(TEMP_SENSOR);
  float R = 1023.f / analogVal - 1.f;
  R *= R0;
  float temperature = (1.f / (log(R / R0) / THERMISTER + 1 / 298.15f) - 273.15f) * 10.f;

  int val = analogRead(BATTERY);
  if(val < 310)
  {
    analogWrite(RGB_RED, 255);
    analogWrite(RGB_GREEN, 0);
    analogWrite(RGB_BLUE, 0);
  }
  else if(val < 325)
  {
    analogWrite(RGB_RED, 128);
    analogWrite(RGB_GREEN, 128);
    analogWrite(RGB_BLUE, 0);
  }
  else
  {
    analogWrite(RGB_RED, 0);
    analogWrite(RGB_GREEN, 255);
    analogWrite(RGB_BLUE, 0);
  }
  
#ifdef _DEBUG
  Serial.print("Temp : ");
  Serial.println(temperature / 10.f);
#endif

  //To set RGB
  RGB curr = { 0 };
  static RGB prev = { 0 };
  prev = curr;
  switch (gColor)
  {
  case eColor::RED_TO_BLUE:
    //RED : (255, 0, 0)
    //BLUE : (0, 0, 255)
    if (temperature >= NORMAL_TEMPERATURE_VARIABLE)
    {
      curr.R = 255;
      curr.G = 255 - 1.7f * (temperature - NORMAL_TEMPERATURE_VARIABLE);
      curr.B = 255 - 1.7f * (temperature - NORMAL_TEMPERATURE_VARIABLE);
    }
    else
    {
      curr.R = 255 - 1.7f * (NORMAL_TEMPERATURE_VARIABLE - temperature);
      curr.G = 255 - 1.7f * (NORMAL_TEMPERATURE_VARIABLE - temperature);
      curr.B = 255;
    }
    break;
  case eColor::ORANGE_TO_PURPLE:
    //ORANGE : (255, 50, 0)
    //PURPLE : (150, 0, 220)
    if (temperature >= NORMAL_TEMPERATURE_VARIABLE)
    {
      curr.R = 255;
      curr.G = 255 - 1.4f * (temperature - NORMAL_TEMPERATURE_VARIABLE);
      curr.B = 255 - 1.7f * (temperature - NORMAL_TEMPERATURE_VARIABLE);
    }
    else
    {
      curr.R = 255 - 0.7f * (NORMAL_TEMPERATURE_VARIABLE - temperature);
      curr.G = 255 - 1.7f * (NORMAL_TEMPERATURE_VARIABLE - temperature);
      curr.B = 255 - 0.23f * (NORMAL_TEMPERATURE_VARIABLE - temperature);
    }
    break;
  default:
    //YELLOW : (255, 255, 0)
    //CYAN : (0, 255, 255)
    if (temperature >= NORMAL_TEMPERATURE_VARIABLE)
    {
      curr.R = 255;
      curr.G = 255;
      curr.B = 255 - 1.7f * (temperature - NORMAL_TEMPERATURE_VARIABLE);
    }
    else
    {
      curr.R = 255 - 1.7f * (NORMAL_TEMPERATURE_VARIABLE - temperature);
      curr.G = 255;
      curr.B = 255;
    }
    break;
  }

  //To Compare curr with prev
  bool bColorChange = (curr.R != prev.R) || (curr.G != prev.G) || (curr.B != prev.B);
  
  //To Emit Light
  if (gbIsBrightnessChanged)
  {
    gCirclePixel.clear();
    gbIsBrightnessChanged = false;
  }
  if (bColorChange)
  {
    for (int i = 0; i < gBrightness; ++i)
    {
      gCirclePixel.setPixelColor(i, curr.R, curr.G, curr.B);
    }
    gCirclePixel.show(); 
  }
}

void ChangeColor()
{
  gColor = (gColor + 1) % 3;
}

void ChangeBrightness()
{
  if ((gBrightness += 2) > 16)
  {
    gBrightness = 2;
  }
  gbIsBrightnessChanged = true;
}

