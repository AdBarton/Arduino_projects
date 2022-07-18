#include <SPI.h> 
#include <RFID.h>
#include <Servo.h> 
#include <SoftwareSerial.h>

//Definice pinu RX a TX pro display
#define RX 7
#define TX 8
SoftwareSerial swSerial(RX,TX);

//Definice pinu 10 a 9 pro RFID
RFID rfid(10, 9);


unsigned char status; 
unsigned char str[MAX_LEN]; //MAX_LEN is 16: size of the array 

String accessGranted [3] = {"5131151027", "8011010022","1572131411312"};
String items[3]={"Pepr","Kari","Sul"};
int accessGrantedSize = 3;                                //The number of serial numbers

Servo lockServo;
int lockPos = 15;              
int unlockPos = 75;             
boolean locked = true;

int redLEDPin = 5;
int greenLEDPin = 6;

void setup() 
{ 
  swSerial.begin(9600);
  Serial.begin(9600);
  SPI.begin(); 
  rfid.init();
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  digitalWrite(redLEDPin, HIGH);
  delay(200);
  digitalWrite(greenLEDPin, HIGH);
  delay(200);
  digitalWrite(redLEDPin, LOW);
  delay(200);
  digitalWrite(greenLEDPin, LOW);
  lockServo.attach(3);
  lockServo.write(lockPos);
  Serial.println("Place card/tag near reader...");
} 

void loop() 
{ 
  if (rfid.findCard(PICC_REQIDL, str) == MI_OK)
  { 
    Serial.println("Card found"); 
    String temp = "";
    if (rfid.anticoll(str) == MI_OK)
    { 
      Serial.print("The card's ID number is : "); 
      for (int i = 0; i < 4; i++)
      { 
        temp = temp + (0x0F & (str[i] >> 4)); 
        temp = temp + (0x0F & str[i]); 
      } 
      Serial.println (temp);
      checkAccess (temp);
    } 
    rfid.selectTag(str);
  }
  rfid.halt();
}

void checkAccess (String temp)
{
  boolean granted = false;
  for (int i=0; i <= (accessGrantedSize-1); i++)
  {
    if(accessGranted[i] == temp)
    {
      sendData(items[i],temp);
      Serial.println ("Access Granted");
      granted = true;
      if (locked == true)
      {
          lockServo.write(unlockPos);
          locked = false;
      }
      else if (locked == false)
      {
          lockServo.write(lockPos);
          locked = true;
      }
      digitalWrite(greenLEDPin, HIGH);
      delay(200);
      digitalWrite(greenLEDPin, LOW);
      delay(200);
      digitalWrite(greenLEDPin, HIGH);
      delay(200);
      digitalWrite(greenLEDPin, LOW);
      delay(200);
    }
  }
  if (granted == false)
  {
    Serial.println ("Access Denied");
    digitalWrite(redLEDPin, HIGH);
    delay(200);
    digitalWrite(redLEDPin, LOW);
    delay(200);
    digitalWrite(redLEDPin, HIGH);
    delay(200);
    digitalWrite(redLEDPin, LOW);
    delay(200);
  }
}

void sendData(String data,String id){
    swSerial.print("t0.txt=\""+data+"\"");
    swSerial.write(0xff);
    swSerial.write(0xff);
    swSerial.write(0xff);

    swSerial.print("t3.txt=\""+id+"\"");
    swSerial.write(0xff);
    swSerial.write(0xff);
    swSerial.write(0xff);  
}
