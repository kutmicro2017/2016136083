const int PIN_RED = 2;
const int PIN_BLUE = 4;
const int PIN_GREEN = 3;

int val;

void setup()
{
  // put your setup code here, to run once:
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
//  for(val=255; val>0; --val)
//  {
//    analogWrite(PIN_RED, val);
//    analogWrite(PIN_BLUE, 255-val);
//    analogWrite(PIN_GREEN, 128-val);
//    delay(1);
//  }
//
//  for(val=0; val<255; ++val)
//  {
//    analogWrite(PIN_RED, val);
//    analogWrite(PIN_BLUE, 255-val);
//    analogWrite(PIN_GREEN, 128-val);
//    delay(1);
//  }

  analogWrite(PIN_RED, 0);
  analogWrite(PIN_BLUE, 0);
  analogWrite(PIN_GREEN, 255);
  delay(2000);

  analogWrite(PIN_RED, 255);
  analogWrite(PIN_BLUE, 0);
  analogWrite(PIN_GREEN, 255);
  delay(2000);

  analogWrite(PIN_RED, 255);
  analogWrite(PIN_BLUE, 0);
  analogWrite(PIN_GREEN, 0);
  delay(2000);

  Serial.println(val, DEC);
}
