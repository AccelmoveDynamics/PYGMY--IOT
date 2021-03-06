#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"

#define DHTPIN D3  
#define DHTTYPE DHT11   // DHT 11
//enter your auth,ssid and password

char auth[] = "enter your auth token";
char ssid[] = "enter your wifi name";
char pass[] = "enter your wifi password";

BlynkTimer timer;
DHT dht(DHTPIN, DHTTYPE);
void myTimerEvent()
{
  float humi = dht.readHumidity();
  float temper = dht.readTemperature();

  if (isnan(humi) || isnan(temper)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else
  {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.println(temper);
    Blynk.virtualWrite(V1, humi); 
    Blynk.virtualWrite(V2, temper);
  }
}
void setup()
{
  // Debug console
  Serial.begin(115200);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
