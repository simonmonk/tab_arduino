

#include <CapacitiveSensor.h>
#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator

// use: Oscil <table_size, update_rate> oscilName (wavetable)
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);
CapacitiveSensor cs = CapacitiveSensor(11, 12);     

const float frequencyScaling = 1.0;

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // powers of 2 please


void setup()
{
  Serial.begin(9600);
  startMozzi(CONTROL_RATE);
  aSin.setFreq(440);
}


void updateControl()
{
  float s = takeReading();
  aSin.setFreq(s);
}


int updateAudio()
{
  return aSin.next(); 
}

void loop()
{
  audioHook();
}


float takeReading()
{
  long reading = cs.capacitiveSensor(5);
  //Serial.println(reading);
  return float(reading) * frequencyScaling;
}
