const int powerPin = 6;
const int ledPin = 5;
const int buzzerPin = 9;
const int meterPin = 10;
const int sensePin = 2;

const int smoothingFactor = 20;

long cancelTime = 0;
long lastEventTime = 0;
long cpm = 0;
boolean cancelled = true;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(sensePin, INPUT);
  tone(powerPin, 1500);
  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(sensePin))
  {
    event();
  }
  else if (! cancelled && millis() > cancelTime)
  {
    digitalWrite(ledPin, LOW);
    analogWrite(buzzerPin, 0);
    cancelTime = millis();
    cancelled = true;
  }
}

void event()
{
  long eventTime = millis();
  digitalWrite(ledPin, HIGH);
  analogWrite(buzzerPin, 127);
  cancelled = false;
  cancelTime = eventTime + 10;
  
  long elapsed = eventTime - lastEventTime;
  long newCpm = 60000 / elapsed;
  cpm = (newCpm * smoothingFactor / 100) 
          + (cpm * (100 - smoothingFactor) / 100);
  // 500 cpm fsd
  int meterValue = cpm * 255 / 500;
  if (meterValue > 255) meterValue = 255;
  analogWrite(meterPin, meterValue);
  Serial.println(meterValue);
  lastEventTime = eventTime;
  delay(100);
}
