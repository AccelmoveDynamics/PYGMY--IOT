
const int ledPin = 5;//D1 pin
const int ldrPin = A0;
int ldrStatus;

void setup() {

Serial.begin(9600);

pinMode(ledPin, OUTPUT);

pinMode(ldrPin, INPUT);

}

void loop() {

int ldrStatus = analogRead(ldrPin);//read light intensity 

if (ldrStatus <=300) {

digitalWrite(ledPin, LOW);
Serial.print(ldrStatus);
Serial.println(" LED is OFF");

}

else {

digitalWrite(ledPin, HIGH);
Serial.println("LED is ON");
Serial.println(ldrStatus);


}

}
