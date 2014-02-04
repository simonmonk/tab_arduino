
#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>

const int numCodes = 5;

// replace with your codes
const char *codes[] = {
  "AD340DD4",
  "FB8A0DD5",
  "9E2455A5",
  "",
  ""
};

const int redPin = 13;
const int greenPin = 12;
const int bluePin = 11;
const int lockPin = 10;

const int red = 0b001;
const int green = 0b010;
const int blue = 0b100;

Adafruit_NFCShield_I2C nfc(2, 3); // IRQ, RESET pins
char code[16]; // hex string of code

void setup(void) 
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(lockPin, OUTPUT);
  setColor(blue);
  
  Serial.begin(9600);
  nfc.begin();
  nfc.setPassiveActivationRetries(0xFF);
  nfc.SAMConfig(); // configure board to read RFID tags
  Serial.println("Scan a tag");
}

void loop() 
{
  if (scanCode())
  {
    checkCode();
  }
  delay(100);
}

boolean scanCode()
{
  boolean success;
  byte uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  byte uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
  
  if (success) 
  {
    Serial.print("Tag Code: ");
    for (uint8_t i=0; i < uidLength; i++) 
    {
      char hexDigits[3];
      sprintf(hexDigits, "%02X", uid[i]);
      code[i*2] = hexDigits[0];
      code[i*2+1] = hexDigits[1];
    }
    code[uidLength*2] = '\0';
    Serial.println(code);
  }
  return success;
}

void checkCode()
{
  boolean codeValid = false;
  for (int i = 0; i < numCodes; i++)
  {
    if (strcmp(code, codes[i]) == 0)
    {
      codeValid = true;
    }
  }
  if (codeValid)
  {
    unlockDoor();
  }
  else
  {
    setColor(red);
    delay(2000);
    setColor(blue);
  }
}

void unlockDoor()
{
  setColor(green);
  digitalWrite(lockPin, HIGH);
  delay(5000); // 5 seconds to get in
  digitalWrite(lockPin, LOW);
  setColor(blue);
}


void setColor(int color)
{
  digitalWrite(redPin, bitRead(color, 0));
  digitalWrite(greenPin,  bitRead(color, 1));
  digitalWrite(bluePin,  bitRead(color, 2));
}  
