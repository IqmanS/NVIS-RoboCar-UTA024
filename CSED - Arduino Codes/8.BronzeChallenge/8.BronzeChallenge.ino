#include<NewPing.h>                 //Library for sonar for ultrasonic sensor
bool start = false;                 //init start off
const int trigPin = 13;             //trig pin for ultrasonic sensor, already connected to pin 13 in buggy
const int echoPin = 12;             //echo pin for ultrasonic sensor, already connected to pin 12 in buggy
const int maxDistance  = 20;        //maximum distance sonar will ping
NewPing sonar(trigPin,echoPin,maxDistance); //creating a sonar object 
int distanceCm;                     //store distance measured from ultrasonic (ping_cm())
int counter = 0;                    //Black Black counter
int prevGantry = 0;                 //last gantry
unsigned long prevTime = millis();  //so that black black time duration is not too small
unsigned long currentTime;

void setup() {
  pinMode(5,OUTPUT);              //Right Tyre +ve
  pinMode(6,OUTPUT);              //Right Tyre -ve
  pinMode(7,OUTPUT);              //Left Tyre +ve
  pinMode(8,OUTPUT);              //Left Tyre -ve
  pinMode(A0,INPUT);              //Left IR
  pinMode(A1,INPUT);              //Right IR
  pinMode(A2,INPUT);              //Reciever
  pinMode(trigPin,OUTPUT);        
  pinMode(echoPin,INPUT);
  Serial.begin(9600);             //Zigbee Communication Baud Rate
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
    char a = Serial.read();               //Read char input from Zigbee
    if(a=='x')                            //If input char is == 'x' start operation
    {
      start =true;
    }
  }
    if(start)                             //starts operation
    { 
      int d0 = digitalRead(A0);           //Left IR D/O
      int d1 = digitalRead(A1);           //Right IR D/O
      int g = pulseIn(A2,HIGH,5000);      //PulseIn from reciever ckt
      if(g>=500 && g<1000 && prevGantry!=1)
      {
        Serial.println("gantry 111");
        Stop();
        delay(1000);
        prevGantry = 1;
      }
      else if(g>=1000 && g<2000 && prevGantry!=2)
      {
        Serial.println("gantry 222");
        Stop();
        delay(1000);
        prevGantry = 2;
      }
      else if(g>=2000 && g<3000 && prevGantry!=3)
      {
        Serial.println("gantry 333");
        Stop();
        delay(1000);
        prevGantry = 3;
      }
      if(d0 == 0 && d1 == 0)                        //Black Black from both sensors
      { 
        currentTime = millis();
        if(currentTime-prevTime>500 && counter == 0)
        {
          //Parking Line
          prevTime = millis();
          counter=counter+1; //counter 1
          Forward();
          delay(25);
        }
        else if(currentTime-prevTime>750 && counter == 1)
        {
          prevTime = millis();
          counter=counter+1; //counter 2
          Left();
          delay(20);
        }
        else if(currentTime-prevTime>1000 && counter == 2)
        {
          //out
          prevTime = millis();
          counter=counter+1; //counter 3
          Forward();
          delay(13);
        }
        else if(currentTime-prevTime>1000 && counter == 3)
        {
          //in
          prevTime = millis();
          counter=counter+1; // counter 4
          Left();
          delay(150);
        }
        else if(currentTime-prevTime>500 && counter == 4)
        {
          //parking 1
          prevTime = millis();
          counter=counter+1;
          Forward();
          delay(10);
        }
        else if (currentTime-prevTime>500 && counter >= 5)
        {
          Serial.println("Buggy Parked");
          Stop();
          start = false;
        }
        Serial.print("Black Black: ");
        Serial.println(counter);
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
    distanceCm = sonar.ping_cm();             // Ultrasonic sensor detects obstable in the range of distance 0 to 15 cm.
    if(distanceCm>0 && distanceCm<15)         // Obstacle Detected
    {
      Stop();
      delay(500);
    }
}
