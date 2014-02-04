
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;
const int lockPin = 12;
const int buzzerPin = 13;
const int knockPin = A0;

const int red = 0b001;
const int green = 0b010;
const int blue = 0b100;

void setup()                    
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(lockPin, OUTPUT);
  pinMode(buzzerPin, INPUT_PULLUP);
  //lockDoor();
  Serial.begin(9600);
 // while(!Serial);
  Serial.println("Here");
}

void loop()                    
{
  int r = analogRead(knockPin);
  if (r > 0)
  {
    Serial.println(r);
  }
}

void unlockDoor()
{
  setColor(green);
  //tone(buzzerPin, 500);
  digitalWrite(lockPin, HIGH);
  delay(5000); // 5 seconds to get in
  digitalWrite(lockPin, LOW);
  //noTone(buzzerPin);
  lockDoor();
}

void lockDoor()
{
  setColor(red);
  digitalWrite(lockPin, LOW);
  for (int i = 0; i < 5; i++)
  {
    setColor(0);
   // tone(buzzerPin, 1000);
    delay(500);
    setColor(red);
   // noTone(buzzerPin);
    delay(500);
  }
}

void setColor(int color)
{
  digitalWrite(redPin, bitRead(color, 0));
  digitalWrite(greenPin,  bitRead(color, 1));
  digitalWrite(bluePin,  bitRead(color, 2));
}  
