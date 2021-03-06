#include <ThingSpeak.h>               // add librery
#include <ESP8266WiFi.h>

WiFiClient  client;
unsigned long counterChannelNumber = xxxx;                // enter Channel ID
const char * myCounterReadAPIKey = "enter your read API key";      // Read API Key
char auth[] = "enter your auth ";
char ssid[] = "enter your ssid";
char pass[] = "enter your password";
const int FieldNumber1 = 1;                                 // The field you wish to read
uint8_t LEDpin = D6;
unsigned int presentValue = 0;
unsigned int changeValue = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid,pass);                 // write wifi name & password

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

void loop()
{
  int A = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
  presentValue = A;
  if (presentValue != changeValue)
  {
    Serial.println(A);
    analogWrite(LEDpin , A);
    changeValue = presentValue;
  }
}
