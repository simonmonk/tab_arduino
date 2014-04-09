
// Arduino Uno or (Leonardo with Ethernet SHield R3)
#include "DHT.h"
#include <SPI.h>
#include <Ethernet.h>

// MAC address just has to be unique. This should work
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetServer server(80);
DHT dht;

const int plusPin = A5;
const int dataPin = A4;
const int ignorePin = A3;
const int gndPin = A2;

char line1[100];

void setup()
{
  pinMode(ignorePin, INPUT);
  pinMode(gndPin, OUTPUT);
  pinMode(plusPin, OUTPUT);
  digitalWrite(plusPin, HIGH);
  pinMode(dataPin, INPUT_PULLUP);
  Serial.begin(9600);
  while (!Serial){};
  connectToNetwork();
  server.begin();
  dht.setup(dataPin);
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

void loop()
{
  EthernetClient client = server.available();
  if (client) 
  {
    while (client.connected()) 
    {
      readHeader(client);
      if (! pageNameIs("/"))
      {
        client.stop();  
        return;
      }
      
      float tempC = dht.getTemperature();
      float tempF = tempC * 9.0 / 5.0 + 32.0;
      float humidity = dht.getHumidity();
      
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println();

      // send the body
      client.println("<html>");
      client.println("<head><script>setTimeout((function(){window.location.reload(true);}), 1000)</script></head>");
      client.println("<body>");
      client.println("<h1>Sensors</h1>");

      client.println("<table>");
      client.println("<tr><th>Temperature (C)</th>");
      client.print("<td>"); client.print(tempC); client.println("</td>");
      client.println("</tr>");
      
      client.println("<tr><th>Temperature (F)</th>");
      client.print("<td>"); client.print(tempF); client.println("</td>");
      client.println("</tr>");
      
      client.println("<tr><th>Relative Humidity</th>");
      client.print("<td>"); client.print(humidity); client.println("</td>");
      client.println("</tr>");
      
      client.println("</table></body></html>");

      client.stop();            
    }
  }
}


void readHeader(EthernetClient client)
{
  // read first line of header
  char ch;
  int i = 0;
  while (ch != '\n')
  {
    if (client.available())
    {
      ch = client.read();
      line1[i] = ch;
      i ++;
    }
  }
  line1[i] = '\0'; 
  Serial.println(line1);
}

boolean pageNameIs(char* name)
{
   // page name starts at char pos 4
   // ends with space
   int i = 4;
   char ch = line1[i];
   while (ch != ' ' && ch != '\n' && ch != '?')
   {
     if (name[i-4] != line1[i])
     {
       return false;
     }
     i++;
     ch = line1[i];
   }
   return true;
}

