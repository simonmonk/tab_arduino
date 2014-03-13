#include <Ethernet.h>
#include <SPI.h>   

// RF Remote pins
int gndPin = A3;
int plusPin = A4;
int bPin = A2;
int cPin = A1;
int dPin = A0;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address

char smtp[] = "smtpcorp.com";
int port = 2525;
char fromEmail[] = "evilgeniusauthor@gmail.com";
char toEmail[] = "srmonk@gmail.com";
char emailBase64[] = "ZXZpbGdlbml1c2F1dGhvckBnbWFpbC5jb20=";
char passwordBase64[] = "QXVndTV0dTU=";

EthernetClient client;

// test on Leonardo
void setup()
{
  Serial.begin(9600);
  delay(1000);
  connectToNetwork();  
  connectToMailServer();

}

void connectToNetwork()
{
  if (Ethernet.begin(mac))
  {
    Serial.println("Connected with DHCP");
    for (byte thisByte = 0; thisByte < 4; thisByte++)
    {
      Serial.print(Ethernet.localIP()[thisByte], DEC);
      Serial.print("."); 
    }
  }
  delay(1000);
  Serial.println();
}

void connectToMailServer()
{
  Serial.println("connecting to SMPT Server...");
  if (client.connect(smtp, port)) 
  {
    Serial.println("Connected to mail server");
    // sendMessage("button pressed");
  } 
  else 
  {
    Serial.println("Connection to mail server failed");
  }
}

void sendMessage(char message[])
{
    client.println("EHLO kltan");
    client.println("AUTH LOGIN");                        
    client.println(emailBase64);          
    client.println(passwordBase64);                                              
    client.print("MAIL FROM:");
    client.println(fromEmail);
    client.print("RCPT TO:");
    client.println(toEmail);
    client.println("DATA");
    client.print("from:");
    client.println(fromEmail);
    client.print("to:");
    client.println(toEmail);
    client.println("SUBJECT: Testing");
    client.println();
    client.println(message);
    client.println(".");
    //client.println(".");
    client.println("QUIT");
}


void loop()
{
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  if (!client.connected()) 
  {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    while(1){}
  }
}
