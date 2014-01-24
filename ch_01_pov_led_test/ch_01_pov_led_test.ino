// ch2_pov_led_test

int ledPins[] = {2, 3, 4, 5, 6, 7, 8};

int gap = 1;

void setup()
{
  for (int i = 0; i < 7; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop()
{
  for (int i = 0; i < 7; i++)
  {
    digitalWrite(ledPins[i], HIGH);
    delay(1000);
  }
}    
        
        
    
