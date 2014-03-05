

const int ledPinA = 6;
const int ledPinB = 5;

void setup()
{
 pinMode(ledPinB, OUTPUT);
 digitalWrite(ledPinB, LOW);
 Serial.begin(9600);
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

