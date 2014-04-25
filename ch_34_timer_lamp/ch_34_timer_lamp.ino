
#include "Wire.h"
#include <Deuligne.h>

const int outputPin = A1;
const int STATE_SETTING = 0;
const int STATE_RUNNING = 1;

const int KEY_LEFT = 3;
const int KEY_RIGHT = 0;
const int KEY_UP = 1;
const int KEY_DOWN = 2;

const int numDelays = 5;
const long delays[] = {10, 30, 60, 120, 300};
static const char labels[numDelays][11] = {
  "10 Seconds", 
  "30 Seconds", 
  "1 Min     ", 
  "2 Mins    ", 
  "5 mins    " };
  
static const char settingPrompt[] = "< and >, v run";
static const char runningPrompt[] = "^ to Cancel   ";

int state = STATE_SETTING;
int delayIndex = 0;
long offTime = 0;

Deuligne lcd;

void setup() 
{
  pinMode(outputPin, OUTPUT);
  lcd.init();
  lcd.clear();
  Serial.begin(9600);
  lcd.print(settingPrompt);
  changeDelay(0);
}

void loop() 
{
  int key = lcd.get_key();
  if (state == STATE_SETTING)
  {
    lcd.setCursor(0, 0);
    if (key == KEY_LEFT)
    {
      changeDelay(-1);
    }
    else if (key == KEY_RIGHT)
    {
      changeDelay(1);
    }
    else if (key == KEY_DOWN)
    {
      lcd.setCursor(0, 0);
      lcd.print(runningPrompt);
      offTime = millis() + delays[delayIndex] * 1000;
      digitalWrite(outputPin, HIGH);
      state = STATE_RUNNING;
    }
  }
  else if (state == STATE_RUNNING)
  {
    if (key == KEY_UP || millis() > offTime)
    {
      digitalWrite(outputPin, LOW);
      lcd.setCursor(0, 0);
      lcd.print(settingPrompt);
      state = STATE_SETTING;
    }
  }
}

void changeDelay(int direction)
{
  delayIndex += direction;
  if (delayIndex < 0) delayIndex = 0;
  if (delayIndex >= numDelays) delayIndex = numDelays;
  lcd.setCursor(0, 1);
  lcd.print(labels[delayIndex]);
  delay(500);
}


