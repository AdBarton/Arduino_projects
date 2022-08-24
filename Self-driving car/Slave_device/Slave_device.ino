//**************************************
// Motors - defines
//**************************************
#define EnableL 5
#define HighL 6  //Left Side motors
#define LowL 7

#define EnableR 10
#define HighR 8  //Right Side motors
#define LowR 9


//**************************************
// Setup
//**************************************
void setup() {
  // put your setup code here, to run once:
  pinMode(EnableL,OUTPUT);
  pinMode(HighL,OUTPUT);
  pinMode(LowL,OUTPUT);

  pinMode(EnableR,OUTPUT);
  pinMode(HighR,OUTPUT);
  pinMode(LowR,OUTPUT);
}

//**************************************
// Forward
//**************************************
void Forward(){
  digitalWrite(HighL,LOW);
  digitalWrite(LowL,HIGH);
  analogWrite(EnableL,255);

  digitalWrite(HighR,LOW);
  digitalWrite(LowR,HIGH);
  analogWrite(EnableR,255);
}

//**************************************
// Backward
//**************************************
void Backward(){
  digitalWrite(HighL,HIGH);
  digitalWrite(LowL,LOW);
  analogWrite(EnableL,255);

  digitalWrite(HighR,HIGH);
  digitalWrite(LowR,LOW);
  analogWrite(EnableR,255);
}

//**************************************
// Right
//**************************************
void Right1(){
  digitalWrite(HighL,LOW);
  digitalWrite(LowL,HIGH);
  analogWrite(EnableL,255);

  digitalWrite(HighR,LOW);
  digitalWrite(LowR,HIGH);
  analogWrite(EnableR,200);
}

void Right2(){
  digitalWrite(HighL,LOW);
  digitalWrite(LowL,HIGH);
  analogWrite(EnableL,255);

  digitalWrite(HighR,LOW);
  digitalWrite(LowR,HIGH);
  analogWrite(EnableR,160);
}

void Right3(){
  digitalWrite(HighL,LOW);
  digitalWrite(LowL,HIGH);
  analogWrite(EnableL,255);

  digitalWrite(HighR,LOW);
  digitalWrite(LowR,HIGH);
  analogWrite(EnableR,100);
}

//**************************************
// Left
//**************************************
void Left1(){
  digitalWrite(HighL,LOW);
  digitalWrite(LowL,HIGH);
  analogWrite(EnableL,200);

  digitalWrite(HighR,LOW);
  digitalWrite(LowR,HIGH);
  analogWrite(EnableR,255);
}

void Left2(){
  digitalWrite(HighL,LOW);
  digitalWrite(LowL,HIGH);
  analogWrite(EnableL,160);

  digitalWrite(HighR,LOW);
  digitalWrite(LowR,HIGH);
  analogWrite(EnableR,255);
}

void Left3(){
  digitalWrite(HighL,LOW);
  digitalWrite(LowL,HIGH);
  analogWrite(EnableL,100);

  digitalWrite(HighR,LOW);
  digitalWrite(LowR,HIGH);
  analogWrite(EnableR,255);
}
//**************************************
// Loop
//**************************************
void loop() {
  Forward();
  delay(500);
  Right3();
  delay(500);
  Forward();
  delay(500);
  Left3();
  delay(500);
  Backward();
  delay(500);
  Right3();
  delay(500);
  Backward();
  delay(500);
  Left3();
  delay(500);
  Backward();
  delay(500);
}
