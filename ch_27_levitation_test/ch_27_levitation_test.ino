const int distancePin = A0;
const int powerPin = 9;

const long pwmTick = 100; // 255 x 100uS = 25.5 mS = 180Hz

int power = 127;
int tick = 0;
long lastTickTime = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available())
  {
    char ch = Serial.read();
    power = (ch - '0') * 255 / 9;
    Serial.print("Power: ");
    Serial.println(power);
  }
  
  long now = micros();
  if (now > lastTickTime + pwmTick)
  {
    digitalWrite(powerPin, tick < power);
    tick ++;
    lastTickTime = now;
    if (tick == power + 1) 
    {
      digitalWrite(powerPin, LOW);
      delay(1);
      Serial.println(analogRead(distancePin));
    }
    if (tick == 255) 
    {
      tick = 0;
    }
  }
}

