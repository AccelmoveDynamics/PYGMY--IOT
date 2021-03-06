int ledpin = 5; // D1
int button = 4; //D2
int buttonState=0;
void setup() {
 pinMode(ledpin, OUTPUT);
 pinMode(button, INPUT);
 Serial.begin(9600); // to begin the monitor
}
void loop() {
 buttonState=digitalRead(button); // put your main code here, to run repeatedly:
 if (buttonState == 0)
 {
 digitalWrite(ledpin,HIGH ); 
 delay(200);
 Serial.println(buttonState);
 }
 if (buttonState==1)
 {
 digitalWrite(ledpin, LOW); 
 delay(200);
 Serial.println(buttonState); // print the value in monitor
 }
}
