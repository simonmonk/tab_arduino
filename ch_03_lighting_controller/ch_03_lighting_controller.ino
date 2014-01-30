// Chapter 4. Lighting Controller

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

int red = 0;
int green = 85;
int blue = 170;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
}

void loop()
{
  red ++; if (red > 255) red = 0;
  analogWrite(redPin, red);
  green ++; if (green > 255) green = 0;
  analogWrite(greenPin, green);
  blue ++; if (blue > 255) blue = 0;
  analogWrite(bluePin, blue);
  delay(20);
}



