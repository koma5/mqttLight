#include <Ethernet.h>
#include <PubSubClient.h>
#include <SPI.h>

int led = 9;
bool check = true;

// Update these with values suitable for your network.
byte mac[]    = {  0x90, 0xA2, 0xDA, 0x60, 0x68, 0x64 };
byte server[] = { 172, 16, 0, 70 };
byte ip[]     = { 172, 16, 0, 44 };

void callback(char* topic, byte* payload, unsigned int length) {
  toggle(led);
}

PubSubClient client(server, 1883, callback);

void setup()
{
  Ethernet.begin(mac, ip);
  pinMode(led, OUTPUT);
}

void loop()
{
  
  if(client.connected())
  {
      client.loop();
      
      if (check)
      {
        client.subscribe("byteli/light/1");
        check = false;
      }
      
  }
  else
  {
    client.connect("arduinoLightControl");
    delay(2000);
  }

  delay(500);
 
}

void toggle(int pin)
{
  if(digitalRead(pin) == HIGH)
  {
    digitalWrite(pin, LOW);
  }
  else
  {
    digitalWrite(pin, HIGH);
  }
}
