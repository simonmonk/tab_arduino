#include "Timer.h"

Timer t;

const long second = 999; // tweak me!
const int pulseLen = 25;

const int pinA[] = {2, 4, 6};
const int pinB[] = {3, 5, 7};

void setup()
{
  for (int i = 0; i < 3; i++)
  {
    pinMode(pinA[i], OUTPUT);
    pinMode(pinB[i], OUTPUT);
  }
  t.every(second, pulse);
}

void loop()
{
  t.update();
}

void pulse()
{
  static int state;
  pulse(state, !state);
  state = ! state;
}

void pulse(int a, int b)
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(pinA[i], a);
    digitalWrite(pinB[i], b);
  }
  delay(pulseLen);
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(pinA[i], LOW);
    digitalWrite(pinB[i], LOW);
  }
}
