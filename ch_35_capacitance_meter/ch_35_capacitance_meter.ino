#include "Wire.h"
#include <Deuligne.h>

const int stepHighCPin = A2;
const int stepLowCPin = A3;
const int sensePin = A1;

const float R1 = 1000.0;
const float R2 = 1000000.0;
const int threshold = 645;  // 63%

// speed up ADC
const byte PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
const byte PS_16 = (1 << ADPS2);

Deuligne lcd;

void setup()
{
  Serial.begin(9600);
  pinMode(stepHighCPin, INPUT);
  pinMode(stepLowCPin, INPUT);
  lcd.init();
  lcd.clear();
  lcd.print("Capacitance");
}

void loop()
{
  float highRange = readC(R1, stepHighCPin, stepLowCPin);
  float reading = highRange;
  if (highRange < 1.0F)
  {
    float lowRange = readC(R2, stepLowCPin, stepHighCPin);
    reading = lowRange;
  }
  display(reading);
  Serial.println(reading * 1000.0);
  delay(500);
}

float readC(float r, int stepPin, int unusedPin)
{
  discharge();
  long t0 = micros();
  charge(stepPin, unusedPin);
  long t1 = micros();
  float T = float(t1 - t0);
  float C = T / r;
  return C;
}

void discharge()
{
  pinMode(stepLowCPin, INPUT);
  pinMode(stepHighCPin, OUTPUT);
  digitalWrite(stepHighCPin, LOW);
  while (analogRead(sensePin) > 0) {};
}

void charge(int stepPin, int unusedPin)
{
  pinMode(unusedPin, INPUT);
  pinMode(stepPin, OUTPUT);
  digitalWrite(stepPin, HIGH);
  while (analogRead(sensePin) < threshold) {};
}

void display(float reading)
{
   if (reading < 0.001)
   {
     clearRow();
     lcd.print("Too Low");
   }
   else if (reading > 0.8)
   {
     clearRow();
     lcd.print(reading);
     lcd.print(" uF");
   }
   else
   {
     clearRow();
     lcd.print(reading * 1000.0);
     lcd.print(" nF");
   }
}

void clearRow()
{
   lcd.setCursor(0, 1);
   lcd.print("                ");
   lcd.setCursor(0, 1);
}
