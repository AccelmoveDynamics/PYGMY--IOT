
#ifdef ENABLE_DEBUG
       #define DEBUG_ESP_PORT Serial
       #define NODEBUG_WEBSOCKETS
       #define NDEBUG
#endif 

#include <Arduino.h>
#include <ESP8266WiFi.h>


#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID         "xxxxxxxxxxxx" //enter your wifi name   
#define WIFI_PASS         "xxxxxxxxxxxx" //enter your wifi password
#define APP_KEY           "xxxxxxxxxxxx"      // enter your app key
#define APP_SECRET        "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"   // enter your app secret 
#define SWITCH_ID_1     "xxxxxxxxxxxxxxxxxxxxxxxxxxx"    // enter your device id


#define BAUD_RATE         9600                // Change baudrate to your need
const int led=D4;

bool onPowerState1(const String &deviceId, bool &state) {
  Serial.printf("Device 1 turned %s\r\n", state?"on":"off");
 if(state){
        digitalWrite(led,HIGH);
        Serial.println(" TURNED ON");
      }
      else{
        digitalWrite(led,LOW);
        }
    return true; // request handled properly
    }
    
  

// setup function for WiFi connection
void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }

  Serial.printf("connected!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str());
}

// setup function for SinricPro
void setupSinricPro() {
  // add devices and callbacks to SinricPro
  SinricProSwitch& mySwitch1 = SinricPro[SWITCH_ID_1];
  mySwitch1.onPowerState(onPowerState1);


  // setup SinricPro
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

// main setup function
void setup() {
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");
  setupWiFi();
   pinMode(led,OUTPUT);
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}
