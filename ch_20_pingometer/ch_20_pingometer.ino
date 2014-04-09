
#include <SPI.h>         
#include <Ethernet.h>
#include <ICMPPing.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; 

IPAddress pingAddr(173, 194, 34, 103); // Google

const int fullScalePing = 500;
const int onTime = 60; // seconds
const int meterPin = 6;

SOCKET pingSocket = 0;

ICMPPing ping(pingSocket, 0);

void setup() 
{
  pinMode(meterPin, OUTPUT);
  connectToNetwork();
  Serial.begin(9600);
  analogWrite(meterPin, 255); // to show meter works
  for (int i = 0; i < onTime * 2; i++)
  {
    ICMPEchoReply echoReply = ping(pingAddr, 4);
    if (echoReply.status == SUCCESS)
    {
      showPingReading(millis() - echoReply.data.time);
    }
    else
    {
      Serial.println("Ping Failed");
      analogWrite(meterPin, 255);
    }
    delay(500);
  }
  analogWrite(meterPin, 0);
}

void loop()
{
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

void showPingReading(long ms)
{
  Serial.println(ms);
  long dutyCycle = ms * 255 / fullScalePing;
  if (dutyCycle < 0) dutyCycle = 0;
  analogWrite(meterPin, dutyCycle);
}





