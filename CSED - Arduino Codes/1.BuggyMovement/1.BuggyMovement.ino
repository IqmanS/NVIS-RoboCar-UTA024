void setup() {
  pinMode(5,OUTPUT); //Right Tyre +ve
  pinMode(6,OUTPUT); //Right Tyre -ve
  pinMode(7,OUTPUT); //Left Tyre +ve
  pinMode(8,OUTPUT); //Left Tyre -ve
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

void loop() {
  Forward();
  delay(3000);
  Left();
  delay(1250);
  Forward();
  delay(3000);
  Left();
  delay(1250);
  Forward();
  delay(3000);
  Left();
  delay(1250);
  Forward();
  delay(3000);
  Left();
  delay(1250);
  Right();
  delay(1500);
  Backward();
  delay(3000);
}
