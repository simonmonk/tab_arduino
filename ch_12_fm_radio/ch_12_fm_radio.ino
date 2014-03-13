#include <Wire.h>
#include <TEA5767Radio.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>

const int buttonPin = 12;

int channel = 0;
  
double freqs[12] = {98.3, 89.0, 91.0, 93.0, 97.4, 103.0, 0.0, 0.0, 0.0, 0.0, 0.0};

TEA5767Radio radio = TEA5767Radio();
Adafruit_7segment display = Adafruit_7segment();

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  Wire.begin();
  radio.setFrequency(freqs[3]);
  display.begin(0x70);
  displayFrequency();
}

void loop()
{
  if (digitalRead(buttonPin) == LOW)
  {
    channel ++;
    if (channel == 12 || freqs[channel] == 0.0)
    {
      channel = 0;
    }
    radio.setFrequency(freqs[channel]);
    displayFrequency();
    delay(300); // debounce key
  }
}

void displayFrequency()
{
  display.clear();
  float f = freqs[channel];
  int f10 = int(f * 10);
  int d4 = f10 % 10;
  f10 = f10 / 10;
  int d3 = f10 % 10;
  f10 = f10 / 10;
  int d2 = f10 % 10;
  f10 = f10 / 10;
  int d1 = f10 % 10;
  f10 = f10 / 10;
  if (d1 > 0)
  {
    display.writeDigitNum(0, d1, false);
  }
  display.writeDigitNum(1, d2, false);
  display.writeDigitNum(3, d3, true);
  display.writeDigitNum(4, d4, false);
  display.writeDisplay();
}

    

