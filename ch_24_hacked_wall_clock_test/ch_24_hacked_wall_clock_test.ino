#include "Timer.h"

Timer t;

const int pinA = 2;
const int pinB = 3;

int pulseLen = 30;

void setup()
{
  Serial.begin(9600);
  while (!Serial) {};
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  Serial.println("Try different pulse lenths starting with the value 30");
  t.every(1000, pulse);
}

void loop()
{
  if (Serial.available())
  {
    pulseLen = Serial.parseInt();
    Serial.print("Pulse set to: ");
    Serial.println(pulseLen);
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
