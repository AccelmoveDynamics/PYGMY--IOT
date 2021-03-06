int mL1= 12;  // initialize D6 as left motor
int mL2= 13;   // initialize D7 as left motor
int mR1= 5; // initialize D1 as right motor
int mR2= 4; //initialize D2 as right motor
void setup() {
// put your setup code here, to run once:
pinMode(mL1,OUTPUT);
pinMode(mL2,OUTPUT);           // Set the input and output values
pinMode(mR1,OUTPUT);
pinMode(mR2,OUTPUT);  
}
void loop()
{
   forward();      // calling the forward function
  delay(1000);   // wait for 1 sec
  stop_now();  
  delay(1000); 
 backward();    // calling the backward function                           
  delay(1000);  // wait for 1 sec
  stop_now();
  delay(1000); 
  right();           // calling the right function
  delay(1000);  // wait for 1 sec
  stop_now(); 
  delay(1000); 
 left();            // calling the left function
 delay(1000);  // wait for 1 sec
 stop_now();
 delay(1000); 
}
void forward()  //To move forward
{
 digitalWrite(mL1,HIGH);
 digitalWrite(mL2,LOW);
 digitalWrite(mR1,HIGH);
 digitalWrite(mR2,LOW);
}
void backward()     // To move Backward
{
 digitalWrite(mL1,LOW);
 digitalWrite(mL2,HIGH);
 digitalWrite(mR1,LOW);
 digitalWrite(mR2,HIGH);
}
 void right()           // To move Right
{
 digitalWrite(mL1,HIGH);
 digitalWrite(mL2,LOW);
 digitalWrite(mR1,LOW);
 digitalWrite(mR2,HIGH);
 } 
 void left() { // To move left
digitalWrite(mL1,LOW);
 digitalWrite(mL2,HIGH); 
digitalWrite(mR1,HIGH);
digitalWrite(mR2,LOW); }  
void stop_now()  //To move forward
{
 digitalWrite(mL1,LOW);
 digitalWrite(mL2,LOW);
 digitalWrite(mR1,LOW);
 digitalWrite(mR2,LOW);
}
