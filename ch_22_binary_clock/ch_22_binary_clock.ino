// Chapter 7. Binary Clock
#include <Wire.h>
#include <RTClib.h>
#include <TimerOne.h>

byte numPins = 5;
byte ledPins[] = {2, 5, 8, 10, 12};

byte hourLeds[][2] = {{1, 3}, {3, 1}, {0, 3}, {3, 0}};
byte minLeds[][2] = {{4, 2}, {3, 4}, {2, 3}, {1, 2}, {0, 1}, {2, 0}};
byte secLeds[][2] = {{2, 4}, {4, 3}, {3, 2}, {2, 1}, {1, 0}, {0, 2}};

RTC_DS1307 RTC;

int hour, min, sec;

void setup()
{
  Wire.begin();
  if (! RTC.isrunning()) 
  {
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  Timer1.initialize(20000); // uS
  Timer1.attachInterrupt( refresh );
}

void loop()
{
  static long lastTick;
  long thisTick = millis();
  if (thisTick > lastTick + 500l) // every 0.5 seconds
  {
    DateTime now = RTC.now();
    hour = now.hour();
    min = now.minute();
    sec = now.second();
    lastTick = thisTick;
  }
  refresh();
}

void refresh()
{
  int s = sec;
  int m = min;
  int h = hour;
  for (int bit = 0; bit < 6; bit++)
  {
    if (s & 1)
    {
      setLed(secLeds[bit]);
     // delay(10);
    }
    s = s >> 1;
    if (m & 1)
    {
      setLed(minLeds[bit]);
    }
    m = m >> 1;
    if (h & 1 && bit < 4)
    {
      setLed(hourLeds[bit]);
    }
    h = h >> 1;
   }
   allOff(); // so last led not brighter
}

void setLed(byte pins[])
{
  byte plusPin = ledPins[pins[0]];
  byte minusPin = ledPins[pins[1]];
  allOff();
  pinMode(plusPin, OUTPUT);
  digitalWrite(plusPin, HIGH);
  pinMode(minusPin, OUTPUT);
  digitalWrite(plusPin, LOW);
}

void allOff()
{  
  for (byte pin = 0; pin < numPins; pin++)
  {
    pinMode(ledPins[pin], INPUT);
  }
}
