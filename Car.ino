//Simple Robot Car

#include <ESP8266WiFi.h> //Upload library

WiFiClient client;
WiFiServer server(80);

const char* ssid = "SOE_ELSD"; //Enter your wifi name
const char* password = "SOE12345"; //Enter your wifi password

String  data =""; 

// define L298N pins
int leftMotorForward = 0;    
int rightMotorForward = 13;  
int leftMotorBackward = 4;   
int rightMotorBackward = 12;  

int rightMotorENB = 14; 
int leftMotorENB = 2;  

int button = 5;   //button
int led = 16;     //LED

void setup()
{
 
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT); 
  pinMode(leftMotorBackward, OUTPUT);  
  pinMode(rightMotorBackward, OUTPUT);

  pinMode(leftMotorENB, OUTPUT); 
  pinMode(rightMotorENB, OUTPUT);

  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);
  
  server.begin();
}

void loop()
{
   
    //test motor
    if(digitalRead(button) == LOW){
      digitalWrite(led, 0);
      //test motor
      MotorForward();
      delay(1000);
      MotorBackward();
      delay(1000);  
      TurnLeft();
      delay(1000);  
      TurnRight();
      delay(1000);  
      MotorStop();
      delay(1000); 
    }
    else{
      digitalWrite(led, 1);
     }
} 


void MotorForward(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}

void MotorBackward(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorBackward,HIGH);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,LOW);
}


void TurnLeft(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH); 
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,HIGH);  
}


void TurnRight(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
}


void MotorStop(void)   
{
  digitalWrite(leftMotorENB,LOW);
  digitalWrite(rightMotorENB,LOW);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}


String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}
