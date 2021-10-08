/*
Full Project Link : https://github.com/ShantonuAcharjee/Arduino-Smart-Dustbin
Author: shantonuacharjee1
Email: shantonuacharjee@gmail.com
YouTube :- http://tinyurl.com/yy374bou
FaceBook: http://tinyurl.com/y52rgdd4Full Project Link :
*/

#include <Servo.h>
 Servo myservoa;
 Servo myservob;
#include <SoftwareSerial.h>
SoftwareSerial gsm(7,8);
String outMessage = "Distbin One Is  Full Plese Clene IT!";
String destinationNumber ="+88017*************";
int trigPinA =A0;
int echoPinA =A1;

int trigPinB =A2;///////MOILA
int echoPinB =A3;


int trigPinC =A4;///////OPEN
int echoPinC =A5;

long durationA;
int distanceA;

long durationB;
int distanceB;

long durationC;
int distanceC;


int flag=0;
int flagA=0;
int flagC=0;
//int led2=12;
//int led3=11;
void setup() 
{
   myservoa.attach(9); 
   myservob.attach(10); 
 pinMode(trigPinA,OUTPUT);
 pinMode(echoPinA,INPUT);

 pinMode(trigPinB,OUTPUT);
 pinMode(echoPinB,INPUT);

 pinMode(trigPinC,OUTPUT);
 pinMode(echoPinC,INPUT);
 //pinMode(13,OUTPUT);
 //pinMode(led2,OUTPUT);
 //pinMode(led3,OUTPUT);
 Serial.begin(9600);
  
}
void loop() {
digitalWrite(trigPinA,LOW);
delayMicroseconds(2);
digitalWrite(trigPinA,HIGH);
delayMicroseconds(10);
digitalWrite(trigPinA,LOW);
durationA=pulseIn(echoPinA,HIGH);
distanceA = durationA*0.034/2;

if(distanceA > 10){
  flag=0;
  //digitalWrite(13,LOW);
  delay(100);

}


 if(distanceA < 6 && flag==0 ){//
delay(200);
flag=1; 
//digitalWrite(13,HIGH);
  
 
  gsm.begin(4800);
  gsm.print("AT+CMGF=1\r");
  delay(1000);
  gsm.println("AT + CMGS = \"" + destinationNumber +"\""); 
  delay(1000);
  gsm.print(outMessage);
  delay(1000);
  gsm.write((char)26);
  
delay(1000);
gsm.println("AT+CLTS=1"); 
gsm.println("AT+CCLK?");
}






digitalWrite(trigPinB,LOW);
delayMicroseconds(2);
digitalWrite(trigPinB,HIGH);
delayMicroseconds(10);
digitalWrite(trigPinB,LOW);
durationB=pulseIn(echoPinB,HIGH);///////MOILA
distanceB = durationB*0.034/2;

if(distanceB < 15 &&  flagA==0){
   flagA=1;
  myservob.write(0); 
   delay(700);//////////choklet
   myservob.write(180);
   //digitalWrite(led2,HIGH);
  myservoa.write(0);///////GATE
  flagC=0;//GATE
}

if(distanceB > 10){
   flagA=0;
   //digitalWrite(led2,LOW);
} 



digitalWrite(trigPinC,LOW);
delayMicroseconds(2);
digitalWrite(trigPinC,HIGH);
delayMicroseconds(10);
digitalWrite(trigPinC,LOW);
durationC=pulseIn(echoPinC,HIGH);///////GAIT OPEN
distanceC = durationC*0.034/2;

if(distanceC < 20 &&  flagC==0){
   flagC=1;
  myservoa.write(90);
 //digitalWrite(led3,HIGH); 
}

//if(distanceC > 20){
   //flagC=0;
  // delay(1300);
   //myservoa.write(0);  
   //digitalWrite(led3,LOW);  
 
//}
//Serial.println(distanceA);

}
