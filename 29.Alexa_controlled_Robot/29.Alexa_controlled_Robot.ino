#ifdef ENABLE_DEBUG
       #define DEBUG_ESP_PORT Serial
       #define NODEBUG_WEBSOCKETS
       #define NDEBUG
#endif 

#include <Arduino.h>
#include <ESP8266WiFi.h>


#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID         "xxxxxxxxxxxxxx" //enter your wifi name
#define WIFI_PASS         "xxxxxxxxxxxxxxxxx" //enter your wifi passward
#define APP_KEY           "xxxxxxxxxxxxxxxxxxxxx"      // enter your app key
#define APP_SECRET        "xxxxxxxxxxxxxxxxxxxx"   // enter your app secret key
#define SWITCH_ID_1       "603c93a4bd5c040a18256dba"    // enter your device_1 id 
#define SWITCH_ID_2       "603ccba7bd5c040a18257472"    // enter your devive_2

#define BAUD_RATE         9600                // Change baudrate to your need id
const int in1 = 12;  //D6
const int in2 = 13;  //D7
const int in3 = 5;  //D1
const int in4 = 4; //D2
int Move =0;
bool onPowerState1(const String &deviceId, bool &state) {
  Serial.printf("Device 1 turned %s\r\n", state?"on":"off");
  if (state == true)
  {
  
     {
    Move +=1;
     }
     
      if (Move==1)
      {
    Serial.println("forward"); // robot move forward
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
      }
     if (Move == 2)
       {  
    Serial.println("backward");// robot move backward
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    Move=0;
   

  }
  }
      else{
    Serial.println("stop");// robot stops
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
        }
    return true; // request handled properly
    }
    
bool onPowerState2(const String &deviceId, bool &state) {
 Serial.printf("Device 2 turned %s\r\n", state?"on":"off");
 if(state){
     Serial.println("left");  //robot move left
     
     digitalWrite(in1,LOW);
     digitalWrite(in2,HIGH);
     digitalWrite(in3,HIGH);
     digitalWrite(in4,LOW);

      }
      else{
     Serial.println("right"); //robot move right
     
     digitalWrite(in1,HIGH);
     digitalWrite(in2,LOW);
     digitalWrite(in3,LOW);
     digitalWrite(in4,HIGH);

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

SinricProSwitch& mySwitch2 = SinricPro[SWITCH_ID_2];
mySwitch2.onPowerState(onPowerState2);

  // setup SinricPro
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

// main setup function
void setup() {
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");
  setupWiFi();
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}
