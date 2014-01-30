// Chapter 5. LED Matrix Clock

#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>

int buttonPin = A0;

RTC_DS1307 RTC;
Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

char* monthNames[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
  "Aug", "Sep", "Oct", "Nov", "Dec"};
  
  
boolean showDate = false;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  Wire.begin();
  if (! RTC.isrunning() || digitalRead(buttonPin) == LOW) 
  {
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  matrix.begin(0x70);
  matrix.setTextWrap(false); 
  matrix.setTextSize(1);
}

void loop()
{
  if (showDate)
  {
    displayDate();
  }
  else
  {
    displayTime();
  }
}

void displayTime()
{
  DateTime now = RTC.now();
  for (int8_t x=7; x>=-36; x--) 
  {
    checkButton();
    if (showDate) 
    {
      delay(500);
      break;
    }
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.setTextColor(LED_GREEN);
    matrix.print(now.hour());
    matrix.setTextColor(LED_YELLOW);
    matrix.print(":");
    matrix.setTextColor(LED_GREEN);
    if (now.minute() < 10)
    {
      matrix.print("0");
    }
    matrix.print(now.minute());   
    matrix.writeDisplay();
    delay(100);
  }
}


void displayDate()
{
  DateTime now = RTC.now();
  for (int8_t x=7; x>=-80; x--) 
  {
    checkButton();
    if (! showDate) 
    {
      delay(500);
      break;
    }
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.setTextColor(LED_RED);
    matrix.print(now.day());
    matrix.setTextColor(LED_YELLOW);
    matrix.print(" ");
    matrix.print(monthNames[now.month() -1]);
    matrix.setTextColor(LED_GREEN);
    matrix.print(" ");   
    matrix.print(now.year());
    matrix.writeDisplay();
    delay(100);
  }
}


void checkButton()
{
  if (digitalRead(buttonPin) == LOW)
  {
    showDate = ! showDate;
  }
}
