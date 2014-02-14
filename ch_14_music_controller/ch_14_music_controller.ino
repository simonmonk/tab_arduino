
const char upKey = 'u';
const char downKey = 'd';
const char leftKey = 'l';
const char rightKey = 'r';

const int gndPin = A2;
const int xPin = 5;
const int yPin = 4;
const int zPin = 3;
const int plusPin = A0;
const int pin3V = A1;

const int tiltThreshold = 30;
const int offset = 340;

void setup()
{
  pinMode(gndPin, OUTPUT);
  digitalWrite(gndPin, LOW);
  pinMode(plusPin, OUTPUT);
  digitalWrite(plusPin, HIGH);
  pinMode(pin3V, INPUT); // 3V output - cxareful!
  //Serial.begin(9600);
  Keyboard.begin();
}

void loop()
{
  int x = analogRead(xPin) - offset;
  int y = analogRead(yPin) - offset;
  //Serial.print(x); Serial.print(" "); Serial.println(y);
  if (y > tiltThreshold)
  {
    Keyboard.print(upKey);
  }
  else if (y < -tiltThreshold)
  {
    Keyboard.print(downKey);
  }
  // not an else if deliberately
  if (x > tiltThreshold)
  {
    Keyboard.print(rightKey);
  }
  else if (x < -tiltThreshold)
  {
    Keyboard.print(leftKey);
  }
  delay(100);
}

