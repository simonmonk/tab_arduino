// Chapter 6. 7 segment Clock

#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>

int buttonPin = A0;

RTC_DS1307 RTC;
Adafruit_7segment display = Adafruit_7segment();
  
boolean showSeconds = false;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  Wire.begin();
  if (! RTC.isrunning() || digitalRead(buttonPin) == LOW) 
  {
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  display.begin(0x70);
}

void loop()
{
  if (digitalRead(buttonPin) == LOW)
  {
    showSeconds = ! showSeconds;
  }
  if (showSeconds)
  {
    displaySeconds();
  }
  else
  {
    displayTime();
  }
}

void displayTime()
{
  static boolean colonState;
  DateTime now = RTC.now();
  int h = now.hour();
  int m = now.minute();
  display.print(h * 100 + m);
  display.drawColon(colonState);
  colonState = ! colonState;
  display.writeDisplay();
  delay(500);
}

void displaySeconds()
{
  DateTime now = RTC.now();
  int s = now.second();
  display.clear();
  display.writeDigitNum(3, s / 10);
  display.writeDigitNum(4, s % 10);
  display.writeDisplay();
  delay(500);
}


