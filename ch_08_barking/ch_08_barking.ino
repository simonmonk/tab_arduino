#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>

int buttonPin = 12;
int pirPin = A0;

SFEMP3Shield MP3player;

void setup() 
{
  MP3player.begin();
  MP3player.SetVolume(0, 0);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(pirPin, INPUT);
  delay(5000);
}

void loop() 
{
  if (digitalRead(buttonPin) == LOW || digitalRead(pirPin) == HIGH)
  {
    MP3player.playTrack(1);
    delay(1000);
  }
}
