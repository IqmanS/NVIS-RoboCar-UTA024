#include<NewPing.h>
bool start = false;
const int trigPin = 13;
const int echoPin = 12;
const int maxDistance  = 20;
NewPing sonar(trigPin,echoPin,maxDistance);
long duration;
int distanceCm;
int prevGantry = 0;

void setup() {
  pinMode(5,OUTPUT); //Right Tyre +ve
  pinMode(6,OUTPUT); //Right Tyre -ve
  pinMode(7,OUTPUT); //Left Tyre +ve
  pinMode(8,OUTPUT); //Left Tyre -ve
  pinMode(A0,INPUT); //Left IR
  pinMode(A1,INPUT); //Right IR
  pinMode(A2,INPUT); //Reciever Ckt
  pinMode(trigPin,OUTPUT); //Trigger Pin Ultrasonic Sensor
  pinMode(echoPin,INPUT);  //Echo Pin Ultrasonic Sensor
  Serial.begin(9600); //Input From ZigBee Module
}

void Forward()
{
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
}
void Backward()
{
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
}
void Left()
{
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
}
void Right()
{
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
}
void Anti()
{
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
}
void Clock()
{
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
}
void Stop()
{
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
}

void loop() {
  if(Serial.available())
  {
    char a = Serial.read();
    if(a=='x')    //Only when the selected char is input from the Coordinator/Router XBee Module, the RoboCar will start its operation.
    {
      start =true;
    }
  }
    if(start)
    {    
      int d0 = digitalRead(A0);       //Input from Left IR Sensor
      int d1 = digitalRead(A1);       //Input from Right IR Sensor
      int g = pulseIn(A2,HIGH,5000);    
      //Before executing change the range of Gantry Pulse
      if(g>500 && g<=1500 && prevGantry!=1)
      {
        Serial.println("gantry 1");
        Stop();
        delay(1000);
        prevGantry = 1;
      }
      else if(g>1500 && g<=2500 && prevGantry!=2)
      {
        Serial.println("gantry 2");
        Stop();
        delay(1000);
        prevGantry = 2;
      }
      else if(g>2500 && g<=3500 && prevGantry!=3)
      {
        Serial.println("gantry 3");
        Stop();
        delay(1000);
        prevGantry = 3;
      } 
          
      if(d0 == 0 && d1 == 0)
      { 
        Forward();
        //Will tackle this condition later
      }
      else if(d0 == 0)
      {
        Left();
      }
      else if(d1 == 0)
      {
        Right();
      }
      else
      {
        Forward();
      }
    }
    distanceCm = sonar.ping_cm();
    if(distanceCm>0 && distanceCm<15 )
    {
      Stop();
      delay(500);
    }
}
