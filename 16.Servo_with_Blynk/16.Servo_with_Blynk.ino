#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo servo;

char auth[] = "enter your auth token"; //  your auth code 
char ssid[] = "enter your wifi name";  // ssid 
char pass[] = "enter your password"; //  password 

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  servo.attach(13); // NodeMCU D7 pin
  
 }
  
void loop()
{
  
  Blynk.run();
  
}
BLYNK_WRITE(V1)
{
   servo.write(param.asInt());
}
