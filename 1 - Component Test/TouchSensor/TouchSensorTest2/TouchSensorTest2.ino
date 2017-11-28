const int PIN_SIG = 2;
const int PIN_GREEN = 13;
const int PIN_RED = 12;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN_SIG, INPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_RED, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  int touchValue = digitalRead(PIN_SIG);
  int touchType = 0;

  if(touchValue == HIGH)
  {
    for(int t=0; t<200; ++t)
    {
      touchValue = digitalRead(PIN_SIG);
      if(touchValue == LOW)
      {
        touchType = 1;
        break;
      }
      if(t==199)
      {
        touchType = 2;
        break;
      }
      delay(10);
    }
  }

  switch(touchType)
  {
    case 1:
      digitalWrite(PIN_GREEN, HIGH);
      digitalWrite(PIN_RED, LOW);
      Serial.println("TOUCHED #1");
      break;
    case 2:
      digitalWrite(PIN_GREEN, LOW);
      digitalWrite(PIN_RED, HIGH);
      Serial.println("TOUCHED #2");
      break;
    default:
      digitalWrite(PIN_GREEN, LOW);
      digitalWrite(PIN_RED, LOW);
      Serial.println("NOT TOUCHED");
      break;
  }
  delay(500);

  if(touchType == 2)
  {
    digitalWrite(PIN_RED, LOW);
    touchValue = digitalRead(PIN_SIG);
    while(touchValue == HIGH)
    {
      touchValue = digitalRead(PIN_SIG);
      if(touchValue == LOW)
      {
        break;
      }
    }
  }
}
