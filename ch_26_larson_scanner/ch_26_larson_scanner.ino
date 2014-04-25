int period = 100;

void setup()
{
  for (int pin = 3; pin < 14; pin++)
  {
    pinMode(pin, OUTPUT);
  } 
}

void loop()
{
  for (int pin = 3; pin < 14; pin++)
  {
    digitalWrite(pin, HIGH);
    delay(period);
    digitalWrite(pin, LOW);
  }
  for (int pin = 12; pin > 3; pin--)
  {
    digitalWrite(pin, HIGH);
    delay(period);
    digitalWrite(pin, LOW);
  }
} 

