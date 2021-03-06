//add libraries:
#include <ESP8266WiFi.h>

#include "Adafruit_MQTT.h"

#include "Adafruit_MQTT_Client.h"
//Now you have to define your network SSID, password, your Adafruit username and your AIO key that you got while doing Adafruit IO setup.

#define WLAN_SSID       "enter your ssid"

#define WLAN_PASS       "enter your pass word"

#define AIO_SERVER      "io.adafruit.com"

#define AIO_SERVERPORT  1883                  

#define AIO_USERNAME    "enter your  user name"

#define AIO_KEY         "enter your key"
//Now you have to define LED to which you are taking your outpu

int output=2;
//Now, create WiFiClient and Adafruit_MQTT_Client objects as global variables, and instantiate the feed for your LED_Control.
WiFiClient client;     // Create an ESP8266 WiFiClient class to connect to the MQTT server.

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);        // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
//MQTT paths for AIO follow the form: <username>/feeds/<feedname>Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe LED_Control = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/LEDSwitch");

void MQTT_connect();

//Now in the setup function we will define our LED pin, baud rate and we will connect to WiFi and MQTT Server.
void setup() {

  Serial.begin(115200);

  delay(10);

pinMode(2,OUTPUT);

 // Connect to WiFi access point.

  Serial.println(); 

  Serial.print("Connecting to ");

  Serial.println(WLAN_SSID);

 

  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println();

 Serial.println("WiFi connected");

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mqtt.subscribe(&LED_Control);

}

uint32_t x=0;
//Now, in the Loop function, we need to check to see if our subscription has been updated, and act accordingly.

void loop() {

   MQTT_connect();

Adafruit_MQTT_Subscribe *subscription;

  while ((subscription = mqtt.readSubscription(5000))) {

    if (subscription == &LED_Control) {

      Serial.print(F("Got: "));

      Serial.println((char *)LED_Control.lastread);

       if (!strcmp((char*) LED_Control.lastread, "ON"))

      {

        digitalWrite(2, HIGH);

      }

      else

      {

        digitalWrite(2, LOW);

      }

    }

  }

}

//Finally, add the MQTT Connect function so that MQTT connection is established.
void MQTT_connect() {

  int8_t ret;

  // Stop if already connected.

  if (mqtt.connected()) {

    return;

  }

 Serial.print("Connecting to MQTT... ");

uint8_t retries = 3;

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected

       Serial.println(mqtt.connectErrorString(ret));

       Serial.println("Retrying MQTT connection in 5 seconds...");

       mqtt.disconnect();

       delay(5000);  // wait 5 seconds

       retries--;

       if (retries == 0) {

         // basically die and wait for WDT to reset me

         while (1);

       }

  }

  Serial.println("MQTT Connected!");

}
