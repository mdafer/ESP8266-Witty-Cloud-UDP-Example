#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//const char* ssid = "ssid";
//const char* password = "password";

WiFiUDP Udp;
const unsigned int localUdpPort = 4210;  // local port to listen on
const unsigned int myseconds = 60000;//1 minute
char incomingPacket[255];  // buffer for incoming packets

int r = 15;
int g = 12;
int b = 13;
bool red = false;
bool green = false;
bool blue = false;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  WiFi.softAP("Dinesh", "password");
  Udp.begin(localUdpPort);
}

// the loop function runs over and over again forever
void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    Serial.println(incomingPacket);
    
    switch(String(incomingPacket).charAt(0))
    {
      case '0':
        red = false;
        green = false;
        blue = false;
        digitalWrite(r, 0);
        digitalWrite(g, 0);
        digitalWrite(b, 0);
      break;
      case '1':
        red = true;
        green = true;
        blue = true;
        digitalWrite(r, 1);
        digitalWrite(g, 1);
        digitalWrite(b, 1);
      break;
      case 'r':
        red = !red;
        digitalWrite(r, red);
      break;
      case 'g':
        green = !green;
        digitalWrite(g, green);
      break;
      case 'b':
        blue = !blue;
        digitalWrite(b, blue);
      break;
    }
    
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
  }
}
