const int analogInPin = A0;

int BatteryValue = 0;
float outputValue = 0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    BatteryValue = analogRead(analogInPin);
    outputValue = (float(BatteryValue)*5)/1023*2;
    Serial.print("Analog value = " );
    Serial.print(BatteryValue);
    Serial.print("\t voltage = ");
    Serial.print(outputValue);
    Serial.print("V \n");
    delay(10);
}
