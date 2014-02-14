
#include <Wire.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>

const int threshold = 100; // cm

int buttonPin = 2;
int trigPin = 8;
int echoPin = 7;

int count = 0;
const int waitingForArrival = 0;
const int waitingForDeparture = 1;
int state = waitingForArrival;

Adafruit_7segment display = Adafruit_7segment();

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Wire.begin();
  display.begin(0x70);
}

void loop()
{
  if (state == waitingForArrival && takeSounding() < threshold)
  {
    state = waitingForDeparture;
  }
  if (state == waitingForDeparture && takeSounding() >= threshold)
  {
    state = waitingForArrival;
    count ++;
  }  
  if (digitalRead(buttonPin) == LOW)
  {
    count = 0;
  }
  display.print(count);
  display.writeDisplay();
  delay(50);
}


int takeSounding()
{
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  int duration = pulseIn(echoPin, HIGH); 
  int distance = duration / 29 / 2;
  return distance;
}
