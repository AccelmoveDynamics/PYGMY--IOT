#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "enter your auth token";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "enter your wifi name";//enter your wifi name
char pass[] = "enter your wifi password ";// enter your wifi password

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
