


#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

EthernetClient client;
Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

const long serverCheckPeriod = 60000;
const int messageLength = 32;

char message[messageLength];
long lastServerContact = -serverCheckPeriod;

void setup() 
{
  Serial.begin(9600);
  while (!Serial){}; // for Leonardo compatability
  matrix.begin(0x70);
  matrix.clear();
  connectToNetwork();
}

void loop() 
{
  long now = millis();
  if (now > lastServerContact + serverCheckPeriod)
  {
    hitWebPage();
    lastServerContact = now;
  }
  displayMessage();
}

void connectToNetwork()
{
  if (Ethernet.begin(mac))
  {
    for (byte thisByte = 0; thisByte < 4; thisByte++)
    {
      Serial.print(Ethernet.localIP()[thisByte], DEC);
      Serial.print("."); 
    }
  }
  delay(3000);
}

void hitWebPage()
{
  Serial.println("Connecting to server");
  if (client.connect("api.openweathermap.org", 80))
  {
    Serial.println("Connected to Server");
    client.println("GET /data/2.5/weather?q=Manchester,uk HTTP/1.0");
    client.println();
    while (client.connected())
    {
      if (client.available())
      {
        Serial.println("Reading Response");
        client.findUntil("description\":\"", "\0");
        String desc = client.readStringUntil('\"');
        if (desc.length() > 0)
        {
          desc.toCharArray(message, messageLength);
        }
      }
    }
    client.stop();
  }
}

void displayMessage()
{
  matrix.setTextWrap(false);  // scroll
  matrix.setTextSize(1);
  matrix.setTextColor(LED_GREEN);
  for (int x = 7; x >= -messageLength*8; x--) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print(message);
    matrix.writeDisplay();
    delay(100);
  }
}
