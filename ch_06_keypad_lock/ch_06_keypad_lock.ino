
#include <Keypad.h>

char* secretCode = "1234";

const byte rows = 4; 
const byte cols = 3; 
char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[rows] = {6, 1, 2, 4}; 
byte colPins[cols] = {5, 7, 3}; 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;
const int lockPin = 12;
const int buzzerPin = 13;

const int red = 0b001;
const int green = 0b010;
const int blue = 0b100;

void setup()                    
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(lockPin, OUTPUT);
  lockDoor();
//  Serial.begin(9600);
//  while(!Serial);
}

void loop()                    
{
  boolean wrong = false;
  while (waitForKey() != '*') {};
  for (int i = 0; i < 4; i++)
  {
    setColor(blue);
    char key = waitForKey();
    if (key == '*') 
    {
      setColor(red);
      break;
    }
    if (key != secretCode[i]) wrong = true;
  }
  if (!wrong) 
  {
    unlockDoor();
  }
  else
  {
    lockDoor();
  }
}

void unlockDoor()
{
  setColor(green);
  tone(buzzerPin, 500);
  digitalWrite(lockPin, HIGH);
  delay(5000); // 5 seconds to get in
  digitalWrite(lockPin, LOW);
  noTone(buzzerPin);
  lockDoor();
}

void lockDoor()
{
  setColor(red);
  digitalWrite(lockPin, LOW);
  for (int i = 0; i < 5; i++)
  {
    setColor(0);
    tone(buzzerPin, 1000);
    delay(500);
    setColor(red);
    noTone(buzzerPin);
    delay(500);
  }
}

char waitForKey()
{
  char key;
  while ((key = keypad.getKey()) == 0) {}; // wait for key down
  while (! keypad.getKey() == 0) {}; // wait for key up  
//  Serial.println(key);
  delay(10);
  return key;
}

void setColor(int color)
{
  digitalWrite(redPin, bitRead(color, 0));
  digitalWrite(greenPin,  bitRead(color, 1));
  digitalWrite(bluePin,  bitRead(color, 2));
}  
