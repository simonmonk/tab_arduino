
const int numberOfPins  = 10;
const int switchPins[] = {5, 7, 4, 2, A2, A4, 6, 3, A3, A5 };
const char keys[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
const long debouncePeriod = 50;

boolean pressed[numberOfPins ];
long lastPressTime[numberOfPins ];


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
