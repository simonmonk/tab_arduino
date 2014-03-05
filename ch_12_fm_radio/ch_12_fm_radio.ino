#include <Adafruit_CharacterOLED.h>
#include <EEPROM.h>
#include <Wire.h>
#include <RTClib.h>
#include <TEA5767Radio.h>

const int radioResetPin = 12;
const int SDIO = A4;
const int SCLK = A5;
const int volumePin = A1;
const int rotaryPin = A0;
const int ampEnable = 11;
const int switchPin = 2;

char* names[12] = {
  "BBC RADIO 1",
  "BBC RADIO 2",
  "BBC RADIO 3",
  "BBC RADIO 4",
  "ROCK FM    ",
  "CH 6       ",
  "CH 7       ",
  "CH 8       ",
  "CH 9       ",
  "CH 10      ",
  "CH 11      ",
  "CH 12      ", 
};
  
double freqs[12] = {98.3, 89.0, 91.0, 93.0, 97.4, 0, 0, 0, 0, 0, 0};

int volume = 0;
int channelNo = 0;

RTC_DS1307 RTC;
TEA5767Radio radio = TEA5767Radio();
Adafruit_CharacterOLED lcd(3,  4,  5, 6,  7,  8,  9);
//                         RS, RW, E, D4, D5, D6, D7

void setup()
{
  Wire.begin();
  RTC.begin();
  Serial.begin(9600);
  pinMode(ampEnable, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  digitalWrite(ampEnable, HIGH);
  lcd.begin(16, 2);
  lcd.print("Starting");
  delay(200);

  if (! RTC.isrunning()) 
  {
    Serial.println("RTC not running");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop()
{
  if (digitalRead(switchPin) == LOW)
  {
    digitalWrite(ampEnable, LOW);
    lcd.setCursor(0, 0);
    lcd.print("            ");
  }
  else
  {
    digitalWrite(ampEnable, HIGH);
    checkChannel();
    displayChannel();
  }
  displayTime();
  delay(10);
}



void checkChannel()
{
  int raw = analogRead(rotaryPin) + 40;
  int newChannelNo = 11 - map(raw, 0, 1023, 0, 11);
  if (channelNo != newChannelNo)
  {
    channelNo = newChannelNo;
    radio.setFrequency(freqs[channelNo]);
    displayChannel();
  }
}

void displayChannel()
{
  lcd.setCursor(0, 0);
  lcd.print(names[channelNo]);
}

void displayTime()
{
  DateTime now = RTC.now();
  int h = now.hour();
  int m = now.minute();
  int s = now.second();
  lcd.setCursor(0, 1);
  lcd.print(h);
  lcd.print(":");
  if (m < 10) lcd.print("0");
  lcd.print(m);
  lcd.print(":");
  if (s < 10) lcd.print("0");
  lcd.print(s);
}



