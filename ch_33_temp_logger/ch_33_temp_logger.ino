#include <EEPROM.h>
#include <Timer.h>


const int lightSensorPin = A0;
const int tempSensorPin = A2;
const int tempGndPin = A1;
const int tempPlusPin = A3;
const int ledPin = 12;
const int maxNumReadings = 1024;
const int switchPin = 11;
const long readingPeriod = 120; // 2 mins (17 hours worth)

boolean recording = false;
int readingIndex = 0;
Timer t;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(tempGndPin, OUTPUT);
  pinMode(tempPlusPin, OUTPUT);
  digitalWrite(tempPlusPin, HIGH);
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
  if (recording && readingIndex < maxNumReadings - 1)
  {
    takeLightReading();
    takeTempReading();
  }
}

void takeLightReading()
{
    digitalWrite(ledPin, LOW);
    int raw = analogRead(lightSensorPin);
    // 0 to 1024 log10 0 to 3
    byte reading = byte(log10(float(raw)) * 80.0);
    Serial.println(reading);
    EEPROM.write(readingIndex, reading);
    readingIndex++;
}


void takeTempReading()
{
    float tempC = readTemp();
    byte reading = byte((tempC + 20.0) * 4);
    Serial.println(tempC);
    EEPROM.write(readingIndex, reading);
    readingIndex++;
}

float readTemp()
{
  int a = analogRead(tempSensorPin);
  float volts = a / 205.0;
  float temp = (volts - 0.5) * 100; 
  return temp;
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
  for (int i = 0; i < maxNumReadings; i += 2)
  {
    Serial.print(EEPROM.read(i));
    Serial.print(",");
    Serial.println(getTempReading(i + 1));
  }
}

float getTempReading(int index)
{
  byte compressedReading = EEPROM.read(index);
  float uncompressesReading = (compressedReading / 4.0) - 20.0;
  return uncompressesReading;
}
