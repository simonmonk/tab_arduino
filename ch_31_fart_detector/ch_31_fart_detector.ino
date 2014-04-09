
const int sensorPin = A2;
const int trimpotPin = A0;
const int buzzerPin = 12;
const int ledPin = 11;

void setup()
{
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  while(! Serial) {};
  Serial.println("Warming Up...");
  warmUp();
  Serial.println("Ready");
}

void loop()
{
  int reading = analogRead(sensorPin);
  int threshold = analogRead(trimpotPin);
  if (reading > threshold)
  {
    tone(buzzerPin, 500);
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    noTone(buzzerPin);
    digitalWrite(ledPin, LOW);
  }
}

void warmUp()
{
  int d = -1;
  int oldReading = 1023;
  while (d <= 0)
  {
    int reading = analogRead(sensorPin);
    Serial.println(reading);
    d = reading - oldReading;
    oldReading = reading;
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
}
