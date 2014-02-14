

const int ledPinA = A0;
const int ledPinB = A1;

void setup()
{
 pinMode(ledPinB, OUTPUT);
}

void loop()
{
  Serial.println(readLightIntensity());
  delay(500);
}

long readLightIntensity()
{
  // brighter = smaller number
  pinMode(ledPinA, OUTPUT);
  digitalWrite(ledPinA, HIGH);
  digitalWrite(ledPinB, LOW);
  delay(1);
  long startTime = micros();
  pinMode(ledPinA, INPUT);
  while (digitalRead(ledPinA)) {};
  long endTime = micros();
  return endTime - startTime;
}

