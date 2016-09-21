/*
Animatromix:
Control led and servomotor remotly from 
python script


*/
#include <Servo.h> 
Servo myservo1, myservo2;
int servo1pin = 8;
int servo2pin = 7;
int val;

void setup(){
  myservo1.attach(servo1pin);
  myservo2.attach(servo2pin);
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
     
     
     
    } 
    
    
  }
  
  
  
  
}
