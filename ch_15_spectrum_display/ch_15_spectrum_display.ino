#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

const int resetPin = A1;
const int strobePin = A2;
const int analogIn = A0;

const int colors[] = {LED_GREEN, LED_GREEN, LED_GREEN, LED_YELLOW, LED_YELLOW, LED_YELLOW, LED_RED, LED_RED};

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

void setup()
{
  pinMode(resetPin, OUTPUT);
  pinMode(strobePin, OUTPUT);
  matrix.begin(0x70);
}

void loop()
{
  pulsePin(resetPin, 100);
  matrix.clear();
  matrix.drawPixel(7, 0, colors[0]);
  for (int x = 6; x >= 0; x--)
  {
    pulsePin(strobePin, 50);
    int magnitude = analogRead(analogIn) >> 7;
    for (int y = 0; y <= magnitude; y++)
    {
      matrix.drawPixel(x, y, colors[y]);
    }
  }
  matrix.writeDisplay();
}
    
void pulsePin(int pin, int duration)
{
  digitalWrite(pin, HIGH);
  delayMicroseconds(duration);
  digitalWrite(pin, LOW);
  delayMicroseconds(100);
}
  
