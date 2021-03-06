#include <ESP8266WiFi.h>
 
const char* ssid = "enter your ssid(wifi name) ";
const char* password = "enter your password";

uint8_t Pwm1 = D3; //Nodemcu PWM pin 
uint8_t Pwm2 = D4; //Nodemcu PWM pin


int a0 = 12;  //D6 of nodemcu esp8266  
int a1 = 13;  //D7 of nodemcu esp8266    
int a2 = 5;  //D1 of nodemcu esp8266   
int a3 = 4;  //D2 of nodemcu esp8266   


WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
//Declaring l293d control pins as Output
pinMode(a0, OUTPUT);     
pinMode(a1, OUTPUT);     
pinMode(a2, OUTPUT);
pinMode(a3, OUTPUT);    
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address on serial monitor
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");    //URL IP to be typed in mobile/desktop browser
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

 int dir=0,Pw=0;
 
 // Match the request
 if (request.indexOf("/start=1") != -1)  {  
  digitalWrite(a0, HIGH); //Start first motor
  digitalWrite(a1, LOW);

  digitalWrite(a2, HIGH); //Start second motor
  digitalWrite(a3, LOW);
  dir=1;
  
  
}

if (request.indexOf("/stop=2") != -1)  {  
  digitalWrite(a0, LOW); //Stop first motor
  digitalWrite(a1, LOW);

  digitalWrite(a2, LOW); //Stop second motor
  digitalWrite(a3, LOW);
  dir=2;
}

if (request.indexOf("/backward=3") != -1)  {
  digitalWrite(a0, LOW);  //Change First motor rotation direction
  digitalWrite(a1, HIGH);
  
  digitalWrite(a2, LOW); //Change Second motor rotation direction
  digitalWrite(a3, HIGH);
   
  dir=3;
}

if (request.indexOf("/right=4") != -1)  {
  digitalWrite(a0, HIGH);  //Change First motor rotation direction
  digitalWrite(a1, LOW);
  
  digitalWrite(a2, LOW); //Change Second motor rotation direction
  digitalWrite(a3, HIGH);
   
  dir=4;
}
if (request.indexOf("/left=5") != -1)  {
  digitalWrite(a0, LOW);  //Change First motor rotation direction
  digitalWrite(a1, HIGH);
  
  digitalWrite(a2, HIGH); //Change Second motor rotation direction
  digitalWrite(a3, LOW);
   
  dir=5;
}
if (request.indexOf("/Req=2") != -1)  {  
analogWrite(Pwm1, 767);  //Pwm duty cycle 75%
analogWrite(Pwm2, 767);  //Pwm duty cycle 75%
Pw=1;
}
if (request.indexOf("/Req=3") != -1)  { 
analogWrite(Pwm1, 512);  //Pwm duty cycle 50%
analogWrite(Pwm2, 512);  //Pwm duty cycle 50%
Pw=2;
}
if (request.indexOf("/Req=4") != -1)  {  
analogWrite(Pwm1, 255);  //Pwm duty cycle 25%
analogWrite(Pwm2, 255);  //Pwm duty cycle 25%
Pw=3;
}

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  

  client.println("<h1 align=center>Nodemcu Dc motor control over WiFi</h1><br><br>");
  client.println("<br><br>");
  client.println("<a href=\"/start=1\"\"><center><button style=background-color:green;><font color=white >Start Motor</font></button></center></a><br/>");
  client.println("<br><br>");
  client.println("<a href=\"/stop=2\"\"><center><button style=background-color:red;><font color=white >Stop Motor </font></button></center></a><br/>");
  client.println("<br><br>");
  client.println("<a href=\"/backward=3\"\"><center><button style=background-color:skyblue;><font color=white >backward</font></button></center></a><br/>");
  client.println("<br><br>");
   client.println("<a href=\"/right=4\"\"><center><button style=background-color:blue;><font color=white >Right</font></button></center></a><br/>");
  client.println("<br><br>");
   client.println("<a href=\"/left=5\"\"><center><button style=background-color:blue;><font color=white >left</font></button></center></a><br/>");
  client.println("<br><br>");
  
  client.println("<a href=\"/Req=2\"\"><center><button style=background-color:black;><font color=white >Duty cycle 75%</font></button></center></a><br/>");
  client.println("<br><br>");
  client.println("<a href=\"/Req=3\"\"><center><button style=background-color:black;><font color=white >Duty cycle 50% </font></button></center></a><br/>");
  client.println("<br><br>");
  client.println("<a href=\"/Req=4\"\"><center><button style=background-color:black;><font color=white >Duty cycle 25% </font></button></center></a><br/>");
  client.println("<br><br>");
    switch(dir){
      case 1:
            client.println("Motor start rotate forward <br/>" );
        break;
      case 2:
        client.println("Motor stop<br/>" );
        break;  
      case 3:
       client.println("Motor rotating in backward direction<br/>" );
        break; 
      case 4:
       client.println("Motor rotating in right direction<br/>" );
        break; 
      case 5:
       client.println("Motor rotating in left direction<br/>" );
        break;   
   
  }
  

switch(Pw){
      case 1:
        client.println("Pwm duty cycle 75%<br/>" );
        break;
      case 2:
        client.println("Pwm duty cycle 50%<br/>" );
        break;  
      case 3:
        client.println("Pwm duty cycle 25%<br/>" );
        break; 
         

  }
  
  client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
