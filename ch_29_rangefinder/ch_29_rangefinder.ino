
#include "Wire.h"
#include <Deuligne.h>

const int trigPin = 9;
const int echoPin = 10;
const int supplyPin = 8;
const int gndPin = 11;

Deuligne lcd;

void setup() 
{
  lcd.init();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(supplyPin, OUTPUT);
  pinMode(gndPin, OUTPUT);
  digitalWrite(gndPin, LOW);
  digitalWrite(supplyPin, HIGH);
}

void loop() 
{
  lcd.clear();
  lcd.setCursor(0, 0);
  float cm = takeSounding();
  lcd.print(int(cm));
  lcd.print(" cm");
  int inches = int(cm / 2.5);

  lcd.setCursor(0, 1);
  int ft = inches / 12;
  lcd.print(ft);
  lcd.print(" ft, ");
  lcd.print(int(inches) % 12);
  lcd.print(" in");
  delay(500);
}


float takeSounding()
{
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  long duration = pulseIn(echoPin, HIGH, 100000); 
  float distance = duration / 29.0 / 2.0;
  return distance;
}
