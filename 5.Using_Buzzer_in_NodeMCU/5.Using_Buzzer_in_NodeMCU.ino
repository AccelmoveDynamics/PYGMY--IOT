const int buzzer = 13; //buzzer to nodemcu D7 pin
void setup()
{
pinMode(buzzer, OUTPUT); // Set buzzer - pin  13 as an output
}
void loop()
{
tone(buzzer, 1000); // Send 1KHz sound signal
delay(1000); // ...for 1 sec
noTone(buzzer); // Stop sound...
delay(1000); // ...for 1sec
}
