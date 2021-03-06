#define led1 D0
#define led2 D1
void setup()
{pinMode(led1, OUTPUT); // setup the three pin as output:
 pinMode(led2, OUTPUT);

}
void loop() // put the main code here to run repeatedly
{
 digitalWrite(led1, HIGH); // turn the LED on (HIGH is the voltage level)
 delay(1000); // wait for 1s
 digitalWrite(led1, LOW); // turn the LED off by making the voltage LOW
 delay(1000); // wait for 1s
 digitalWrite(led2, HIGH); // turn the LED on (HIGH is the voltage level)
 delay(1000); // wait for 1ms
 digitalWrite(led2, LOW); // turn the LED off by making the voltage LOW
 delay(1000); // wait for 1ms
} 
