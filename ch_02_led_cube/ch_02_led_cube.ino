// Chapter 3. LED Cube

int ledPins[3][3] = {{13, 9, 5}, {12, 10, 6}, {11, 8, 7}};

int layerSelectPins[] = {3, 4, 2};

int model[3][3][3];
long period = 50;
long refreshPeriod = 5;

void setup()
{
  for (int x = 0; x < 3; x++)
  {
    for (int y = 0; y < 3; y++)
    {
      pinMode(ledPins[x][y], OUTPUT);
    }
  }
  pinMode(layerSelectPins[0], OUTPUT);
  pinMode(layerSelectPins[1], OUTPUT);
  pinMode(layerSelectPins[2], OUTPUT);
  
  model[0][0][0] = HIGH;
}

void loop()
{
  static long lastUpdate;
  long now = millis();
  if (now > lastUpdate + period)
  {
   animate();
   lastUpdate = now;
  }
  refresh();
}

void animate()
{
   model[random(3)][random(3)][random(3)] = HIGH;
   model[random(3)][random(3)][random(3)] = LOW;
}

void refresh()
{
  for (int layer = 0; layer < 3; layer++)
  {
    digitalWrite(layerSelectPins[layer], HIGH);
    for (int x = 0; x < 3; x++)
    {
      for (int y = 0; y < 3; y++)
      {
        digitalWrite(ledPins[y][x], model[layer][y][x]);
      }
    }
    delay(refreshPeriod);
    digitalWrite(layerSelectPins[layer], LOW);
  }
}
