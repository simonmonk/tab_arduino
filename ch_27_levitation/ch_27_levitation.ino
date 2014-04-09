
const int distancePin = A0;
const int powerPin = 9;

float kp = 5.0f;
float ki = 0.3f; // %
float kd = 40.0f;
int setDistance = 415;

int power = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("kp ki kd dist");
}

/// try ditching analogwrite and turn it on for power ms, the off for 255 - power ms each time around the loop.
// safe copy.
// measure the position at the end of the 'off period' (always 1)
// tuning params will be completely wrong

void loop()
{
  
  if (Serial.available())
  {
    kp = Serial.parseFloat();
    ki = Serial.parseFloat();
    kd = Serial.parseFloat();
    setDistance = Serial.parseInt();
    Serial.print(kp); Serial.print(" ");
    Serial.print(ki); Serial.print(" ");
    Serial.print(kd); Serial.print(" ");
    Serial.println(setDistance);
        
  }
  
  static float oldError = 0;
  static int oldPower = 0;
  long distance = measureDistance();
  float error = float(setDistance - distance); // negative if too low
  
  // Integration
  error = (error * ki) + (oldError * (1 - ki));
  
  // Derrivative
  float d = error - oldError; // negative means falling
  
  power = int(127 - error * kp - d * kd); // more power if too low
  if (power < 0) power = 0;
  if (power > 255) power = 255;
  if (power != oldPower)
  {
     analogWrite(powerPin, power);
     oldPower = power;
     Serial.println(power);
  }
  delay(10);
}


int measureDistance()
{
  analogWrite(powerPin, 0);
  delayMicroseconds(1000);
  int reading = analogRead(distancePin);
  analogWrite(powerPin, power);
  return reading;
}
