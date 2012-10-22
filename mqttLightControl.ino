#include <Ethernet.h>
#include <PubSubClient.h>
#include <SPI.h>

int led = 9;

// Update these with values suitable for your network.
byte mac[]    = {  0x90, 0xA2, 0xDA, 0x60, 0x68, 0x64 };
byte server[] = { 172, 16, 0, 70 };
byte ip[]     = { 172, 16, 0, 44 };

void callback(char* topic, byte* payload, unsigned int length)
{
  
  if(length == 2 && payload[0] == 'o' && payload[1] == 'n')
  {
    on(led);
  }
  
  if(length == 3 && payload[0] == 'o' && payload[1] == 'f' && payload[2] == 'f')
  {
    off(led);
  }

  if(length == 0 || length == 6 && payload[0] == 't' && payload[1] == 'o' && payload[2] == 'g' && payload[3] == 'g' && payload[4] == 'l' && payload[5] == 'e')
  {
    toggle(led);
  }

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
  }
  else
  {
    client.connect("arduinoLightControl");
    delay(5000);
    client.subscribe("byteli/light/1");
  }
 
}

void on(int pin)
{
  if(digitalRead(pin) == LOW)
  {
    digitalWrite(pin, HIGH);
  }
}

void off(int pin)
{
  if(digitalRead(pin) == HIGH)
  {
    digitalWrite(pin, LOW);
  }
}

void toggle(int pin)
{
  if(digitalRead(pin) == LOW)
  {
    digitalWrite(pin, HIGH);
  }
  else
  {
    digitalWrite(pin, LOW);
  }
}


