

#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator

// use: Oscil <table_size, update_rate> oscilName (wavetable)
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // powers of 2 please

int trigPin = 11;
int echoPin = 12;


void setup()
{
  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
  aSin.setFreq(440); // set the frequency with an unsigned int or a float
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}


void updateControl()
{
  float s = takeSounding();
  aSin.setFreq(s);
}


int updateAudio()
{
  return aSin.next(); // return an int signal centred around 0
}


void loop()
{
  audioHook(); // required here
}


float takeSounding()
{
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  int duration = pulseIn(echoPin, HIGH, 1000); 
  if (duration > 1000) duration = 1000;
  return (float)duration / 2.0;
}

