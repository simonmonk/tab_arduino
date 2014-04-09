const int distancePin = A0;
const int powerPin = 9;

const long pwmTick = 100; // 255 x 100uS = 25.5 mS = 180Hz

int power = 10;
int tick = 0;
long lastTickTime = 0;

long kp = 5;
long ki = 50; // %
long kd = 30;
int setDistance = 260;

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
    if (tick == 255) 
    {
      tick = 0;
      adjustPower();
    }
  }
}

void adjustPower()
{
  digitalWrite(powerPin, LOW);
  delay(1);
  long distance = analogRead(distancePin);
  static long oldError = 0;
  long error = setDistance - distance; // negative if too low
  
  // Integration
  error = (error * ki / 100) + (oldError * (100 - ki) / 100);
  
  // Derrivative
  long d = error - oldError; // negative means falling
  
  power = error * kp - d * kd; // more power if too low
  if (power < 0) power = 0;
  if (power > 255) power = 255;
  Serial.print(power); Serial.print(" "); Serial.print(distance); Serial.print(" "); Serial.println(error); 
}
