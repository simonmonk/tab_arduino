
const char keyNotes[] = "asdfghjk";

const int gndPin = A2;
const int xPin = 5;
const int yPin = 4;
const int zPin = 3;
const int plusPin = A0;
const int pin3V = A1;

const int offset = 340;

void setup()
{
  pinMode(gndPin, OUTPUT);
  digitalWrite(gndPin, LOW);
  pinMode(plusPin, OUTPUT);
  digitalWrite(plusPin, HIGH);
  pinMode(pin3V, INPUT); // 3V output - careful!
  Keyboard.begin();
}

void loop()
{
  static int lastKeyIndex = 0;
  int x = analogRead(xPin) - offset;
  int y = analogRead(yPin) - offset;
  Serial.print(x); Serial.print(" "); Serial.println(y);
  // -50 to + 50
  int keyIndex = (y + 50) / 12;
  if (keyIndex < 0) keyIndex = 0;
  if (keyIndex > 7) keyIndex = 7;
  if (keyIndex != lastKeyIndex && (abs(x) < 20))
  {
    Keyboard.releaseAll();
    Keyboard.press(keyNotes[keyIndex]);
    lastKeyIndex = keyIndex;
    delay(30);
  }
}

