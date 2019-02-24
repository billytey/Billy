//Wifi Robot Car - station mode

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

//Setting PWM properties
const int freq = 500;   //500Hz
int dutyCycle = 512;    //0 - 1023

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

  Serial.begin(115200);        //serial at 115.2kbps

  //connect to AP
  WiFi.begin(ssid,password);  
  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(led, 0);
  Serial.println("success!");
  Serial.print("NodeMCU IP Address is: ");
  Serial.println(WiFi.localIP());
  server.begin();

  //PWM 
   analogWriteFreq(freq);  //500Hz
}

void loop()
{
   
    client = server.available();
    if (!client) return; 
      data = checkClient ();

    Serial.println("OK");
    
    //wifi remote controller
    if (data == "forward") MotorForward();

    else if (data == "reverse") MotorBackward();

    else if (data == "left") TurnLeft();

    else if (data == "right") TurnRight();

    else if (data == "stop") MotorStop();

    sendBackEcho(data); // send command echo back to android device
    data = ""; 
} 


void MotorForward(void)   
{
 // digitalWrite(leftMotorENB,HIGH);
 // digitalWrite(rightMotorENB,HIGH);
  analogWrite(leftMotorENB, dutyCycle);
  analogWrite(rightMotorENB, dutyCycle);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,LOW);
  Serial.println("Motor Forward");
}

void MotorBackward(void)   
{
  //digitalWrite(leftMotorENB,HIGH);
  //digitalWrite(rightMotorENB,HIGH);
  analogWrite(leftMotorENB, dutyCycle);
  analogWrite(rightMotorENB, dutyCycle);
  digitalWrite(leftMotorBackward,HIGH);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,LOW);
  Serial.println("Motor Backward");
}


void TurnLeft(void)   
{
  //digitalWrite(leftMotorENB,HIGH);
  //digitalWrite(rightMotorENB,HIGH);
  analogWrite(leftMotorENB, dutyCycle);
  analogWrite(rightMotorENB, dutyCycle);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,HIGH);  
  Serial.println("Motor Left");
}


void TurnRight(void)   
{
  //digitalWrite(leftMotorENB,HIGH);
  //digitalWrite(rightMotorENB,HIGH);
  analogWrite(leftMotorENB, dutyCycle);
  analogWrite(rightMotorENB, dutyCycle);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  Serial.println("Motor Right");
}


void MotorStop(void)   
{
  //digitalWrite(leftMotorENB,LOW);
  //digitalWrite(rightMotorENB,LOW);
  analogWrite(leftMotorENB, 0);
  analogWrite(rightMotorENB, 0);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
  Serial.println("Motor Stop");
}


String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}


/* send command echo back to android device */
void sendBackEcho(String echo)
{
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println(echo);
  client.println("</html>");
  client.stop();
  delay(1);
}
