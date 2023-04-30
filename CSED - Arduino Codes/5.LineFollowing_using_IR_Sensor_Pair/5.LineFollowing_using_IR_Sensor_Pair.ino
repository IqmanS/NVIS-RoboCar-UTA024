#include<NewPing.h>

const int trigPin = 13;
const int echoPin = 12;
const int maxDistance  = 20;
NewPing sonar(trigPin,echoPin,maxDistance);
long duration;
int distanceCm;

void setup() {
  pinMode(5,OUTPUT); //Right Tyre +ve
  pinMode(6,OUTPUT); //Right Tyre -ve
  pinMode(7,OUTPUT); //Left Tyre +ve
  pinMode(8,OUTPUT); //Left Tyre -ve
  pinMode(A0,INPUT); //Left IR
  pinMode(A1,INPUT;  //Right IR
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);
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

  Forward();
  int d0 = digitalRead(A0);
  int d1 = digitalRead(A1);
  if(d0 == 0 && d1 == 0)
  {
    Forward();
    //Will tackle this condtion later
  }
  else if(d0 ==0)
  {
    Right();
  }
  else if(d1 == 0)
  {
    Left();
  }
  distanceCm = sonar.ping_cm();
  Serial.println(distanceCm);
  if(distanceCm>0 && distanceCm<15 )
  {
    Stop();
    delay(500);
  }  
}
