#include "Timer.h"

Timer t;

const int pinA = 2;
const int pinB = 3;

const int pulseLen = 30;

int event;

void setup()
{
  Serial.begin(9600);
  while (!Serial) {};
  Serial.println("Enter speed 0 to 9 where 5 is normal and 0 is stopped");
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  setTickRate(5);
}

void loop()
{
  if (Serial.available())
  {
    int speed = Serial.parseInt();
    setTickRate(speed);
  }
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
  digitalWrite(pinA, a);
  digitalWrite(pinB, b);
  delay(pulseLen);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
}

void setTickRate(int rate)
{
  // rate is 0 to 9, 0 stopped, 5 normal
  int period = 5000 / rate;
  t.stop(event);
  if (rate > 0)
  {
    event = t.every(period, pulse);
  }
}
