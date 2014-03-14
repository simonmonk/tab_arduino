#include <Ethernet.h>
#include <SPI.h>   

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address

char smtp[] = "smtpcorp.com";
int port = 2525;
char fromEmail[] = "myemail@somemail.com";
char toEmail[] = "myemail@somemail.com";
char emailBase64[] = "hasdfgw456hg56=";
char passwordBase64[] = "hjgwrejtgwrejt=";
char message[] = "A Button was pressed";

EthernetClient client;

// RF Remote pins
int gndPin = A3;
int plusPin = A5;
int vtPin = A4;

void setup()
{
  pinMode(gndPin, OUTPUT);
  digitalWrite(gndPin, LOW);
  pinMode(plusPin, OUTPUT);
  digitalWrite(plusPin, HIGH);
  pinMode(vtPin, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  Serial.begin(9600);
  while (!Serial) {};
  Serial.println("Ready");
}

void loop()
{
  if (digitalRead(vtPin))
  {
    Serial.println("Email Sending Triggered");
    connectToNetwork();  
    connectToMailServer();
    sendMessage(message);
    if (!client.connected()) 
    {
      Serial.println("disconnecting.");
      client.stop();
    }
    delay(3000);
  }
  displayClientResponse();
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
  delay(3000);
  Serial.println();
}

void connectToMailServer()
{
  Serial.println("connecting to SMPT Server...");
  if (client.connect(smtp, port)) 
  {
    Serial.println("Connected to mail server");
    delay(500);
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
    client.println("QUIT");
}

void displayClientResponse()
{
  if (client.available()) 
  {
    char c = client.read();
    Serial.print(c);
  }
}
