
#include "Wire.h"
#include <Deuligne.h>
#include <SoftwareSerial.h>

const int rxPin = 7;
const int txPin = 8; // not used
const int sentenceSize = 80;
char sentence[sentenceSize];


Deuligne lcd;
SoftwareSerial gps(rxPin, txPin); 

void setup() 
{
  lcd.init();
  gps.begin(9600);
  lcd.clear();
  lcd.print("Starting..");
  Serial.begin(9600);
}

void loop() 
{
  static int i = 0;
  if (gps.available())
  {
    char ch = gps.read();
    if (ch != '\n' && i < sentenceSize)
    {
      sentence[i] = ch;
      i++;
    }
    else
    {
     sentence[i] = '\0';
     i = 0;
     displayGPS();
    }
  }
}

void displayGPS()
{
  Serial.println(sentence);
  char field[80];
  getField(field, 0);
  if (strcmp(field, "$GPRMC") == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("Lat: ");
    getField(field, 3);  // number
    lcd.print(field);
    getField(field, 4); // N/S
    lcd.print(field);
    
    lcd.setCursor(0, 1);
    lcd.print("Lon: ");
    getField(field, 5);  // number
    lcd.print(field);
    getField(field, 6);  // E/W
    lcd.print(field);
  }
}

void getField(char* buffer, int index)
{
  int sentencePos = 0;
  int fieldPos = 0;
  int commaCount = 0;
  while (sentencePos < sentenceSize)
  {
    if (sentence[sentencePos] == ',')
    {
      commaCount ++;
      sentencePos ++;
    }
    if (commaCount == index)
    {
      buffer[fieldPos] = sentence[sentencePos];
      fieldPos ++;
    }
    sentencePos ++;
  }
  buffer[fieldPos] = '\0';
}
