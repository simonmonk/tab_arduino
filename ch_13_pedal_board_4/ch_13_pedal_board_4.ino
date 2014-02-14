
const int numberOfPins  = 4;
const int switchPins[] = {7, 2, A0, 12};
const char keys[] = {'a', 's', 'w', 'z'};
const long debouncePeriod = 50;

boolean pressed[numberOfPins];
long lastPressTime[numberOfPins];


void setup()
{
  for (int i = 0; i < numberOfPins ; i++)
  {
    pinMode(switchPins[i], INPUT_PULLUP);
  }
  Keyboard.begin();
}

void loop()
{
  for (int i = 0; i < numberOfPins ; i++)
  {
    boolean keyPressed = (digitalRead(switchPins[i]) == LOW);
    long timeNow = millis();
    boolean tooSoon = (timeNow < lastPressTime[i] + debouncePeriod);
    if (keyPressed)
    {
      if (pressed[i] == false && ! tooSoon)
      {
        Keyboard.print(keys[i]);
        lastPressTime[i] = timeNow;
        pressed[i] = true;
      }
    }
    else
    {
      pressed[i] = false;
    }
  }
}
