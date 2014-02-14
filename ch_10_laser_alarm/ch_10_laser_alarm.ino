

const int ledPinA = A0;
const int ledPinB = A1;
const int laserPin = A5;
const int buttonPin = 8;
const int alarmPin = 9;

const int threshold = 100;

boolean alarmTriggered = false;

void setup()
{
 pinMode(laserPin, OUTPUT);
 pinMode(ledPinB, OUTPUT);
 pinMode(buttonPin, INPUT_PULLUP);
 pinMode(alarmPin, OUTPUT);
}

void loop()
{
  if (! laserOnTarget())
  {
    alarmTriggered = true;
  }
  if (digitalRead(buttonPin) == LOW)
  {
    alarmTriggered = false;
  }
  digitalWrite(alarmPin, alarmTriggered);
  if (alarmTriggered)
  {
    flashLED();
  }
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

boolean laserOnTarget()
{
  long readingWithLaser = readLightIntensity(); 
  digitalWrite(laserPin, LOW);
  delay(10);
  long readingNoLaser = readLightIntensity();
  digitalWrite(laserPin, HIGH);
  return (readingWithLaser < readingNoLaser - threshold);
}

void flashLED()
{
  pinMode(ledPinA, OUTPUT);
  digitalWrite(ledPinA, LOW);
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(ledPinB, HIGH);
    delay(200);
    digitalWrite(ledPinB, LOW);
    delay(200);
  }
}
  
