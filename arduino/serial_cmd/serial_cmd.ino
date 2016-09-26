/*
Animatromix:
Control led and servomotor remotly from 
python script


*/
#include <Servo.h> 
Servo myservo1, myservo2;
int servo1pin = 27;
int servo2pin = 29;
int rubLed1pin = 9;
int ledRGBrpin = 8;
int ledRGBgpin = 6;
int ledRGBbpin = 7;
int val;

void setup(){
  myservo1.attach(servo1pin);
  myservo2.attach(servo2pin);
  pinMode(rubLed1pin, OUTPUT );
  pinMode(ledRGBrpin, OUTPUT );
  pinMode(ledRGBgpin, OUTPUT ); 
  pinMode(ledRGBbpin, OUTPUT );
  Serial.begin(115200);

}

void loop(){
 
  if(Serial.available() == 2 ){
   
     char id = Serial.read();
     char val = Serial.read();
    
    switch(id){
       case 7:
         myservo1.write(map(val, 0 , 127, 0, 180));
       break;
       case 4:
         myservo2.write(map(val, 0 , 127, 0, 180));
       break;
       case 2:
         analogWrite(rubLed1pin, map(val, 1, 127, 0, 255));
       break;
       case 10:
         analogWrite(ledRGBrpin, map(val, 1, 127, 0, 255));
       break;
       case 11:
         analogWrite(ledRGBrpin, map(val, 1, 127, 0, 255));
       break;
       case 12:
         analogWrite(ledRGBrpin, map(val, 1, 127, 0, 255));
       break;
     
     
     
    } 
    
    
  }
  
  
  
  
}
