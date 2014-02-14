
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;
const int lockPin = 12;
const int buzzerPin = 13;
const int knockPin = A0;

const int red = 0b001;
const int green = 0b010;
const int blue = 0b100;

const int threshold = 3;
const int ignorePeriod = 60; // milliseconds
const int tapLeeway = 200; // milliseconds
const int maxRecordTime = 5000;
const int maxTaps = 30;
long key[maxTaps];
long guess[maxTaps];

void setup()                    
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(lockPin, OUTPUT);
  setColor(blue);
  recordKnock(key);
  playKnock(key);
  delay(500);
  lockDoor();
 // Serial.begin(9600);
//  while(!Serial);
}

void loop()                    
{
  if (tapDetected())
  {
    delay(100);
    setColor(blue);
    delay(100);
    recordKnock(guess);
    if (guessCorrect())
    {
      unlockDoor();
    }
    else
    {
      lockDoor();
    }
  }
}

void recordKnock(long buffer[])
{
  //Serial.println("Recording for 5 seconds");
  int i = 1;
  long t0 = millis();
  long t = 0;
  while (((t = millis()) < t0 + maxRecordTime) && (i < maxTaps))
  {
    if (tapDetected())
    {
      Serial.print(".");
      buffer[i] = t - t0;
      i++;
    }
  }
  buffer[0] = i;
  //Serial.print("knocks: ");
  //Serial.println(i-1);
}


boolean tapDetected()
{
  if (analogRead(knockPin) > threshold)
  {
    delay(ignorePeriod); // ignore ringing
    return true;
  }
  return false;
}

void playKnock(long buffer[])
{
  long t0 = millis();
  long prevTap = 0;
  for (int i = 1; i < buffer[0]; i++)
  {
    delay(buffer[i] - prevTap);
    tone(buzzerPin, 500);
    delay(10);
    noTone(buzzerPin);
    prevTap = buffer[i];
  }
}

boolean guessCorrect()
{
  if (key[0] != guess[0])
  {
    //Serial.println("wrong number of knocks");
    return false;
  }
  // find delay before first tap
  long startGap = guess[1] - key[1];
  for (int i = 1; i < key[0]; i++)
  {
    long error = abs(guess[i] - key[i] - startGap);
    //Serial.print(i); Serial.print(" "); Serial.print(guess[i]); Serial.print(" "); Serial.print(key[i]); Serial.print(" "); Serial.println(error);
    if (error > tapLeeway)
    {
      return false;
    }
  }
  return true;
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

void setColor(int color)
{
  digitalWrite(redPin, bitRead(color, 0));
  digitalWrite(greenPin,  bitRead(color, 1));
  digitalWrite(bluePin,  bitRead(color, 2));
}  
