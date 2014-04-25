#include <EEPROM.h>
#include <Timer.h>


const int sensorPin = A0;
const int ledPin = 12;
const int maxNumReadings = 1024;
const int switchPin = 11;
const long readingPeriod = 60; // 60 seconds (17 hours worth)

boolean recording = false;
int readingIndex = 0;
Timer t;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  Serial.begin(9600);
  while (! Serial) {};
  Serial.println("d-download c-clear");
  t.every(readingPeriod * 1000L, takeReading);
  t.every(1000, updateLED);
}

void loop()
{
  if (Serial.available())
  {
    char ch = Serial.read();
    if (ch == 'd')
    {
      recording = false;
      dump();
    }
    else if (ch == 'c')
    {
      recording = false;
      clear();
    }
  }
  if (digitalRead(switchPin) == LOW)
  {
    recording = true;
  }
  t.update();
}

void takeReading()
{
  if (recording && readingIndex < maxNumReadings)
  {
    digitalWrite(ledPin, LOW);
    int raw = analogRead(sensorPin);
    // 0 to 1024 log10 0 to 3
    byte reading = byte(log10(float(raw)) * 80.0);
    Serial.println(reading);
    EEPROM.write(readingIndex, reading);
    readingIndex++;
  }
}

void updateLED()
{
  if (recording)
  {
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
  }
}

void clear()
{
  for (int i = 0; i < maxNumReadings; i++)
  {
    EEPROM.write(i, 0);
  }
  readingIndex = 0;
  Serial.println("Cleared");
}

void dump()
{
  for (int i = 0; i < maxNumReadings; i++)
  {
    Serial.println(EEPROM.read(i));
  }
}
