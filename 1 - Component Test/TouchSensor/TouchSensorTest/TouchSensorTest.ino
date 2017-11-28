const int PIN_SIG = 2;
const int PIN_LED = 13;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN_SIG, INPUT);
  pinMode(PIN_LED, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  int touchValue = digitalRead(PIN_SIG);

  if(touchValue == HIGH)
  {
    digitalWrite(PIN_LED, HIGH);
    Serial.println("TOUCHED");
  }
  else
  {
    digitalWrite(PIN_LED, LOW);
    Serial.println("NOT TOUCHED");
  }
  
  delay(500);
}
