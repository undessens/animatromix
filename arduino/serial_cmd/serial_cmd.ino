/*
Animatromix:
Control stepper motor, led and servomotor remotly from 
python script


*/

#include <Servo.h> 
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

/* TODO 
Don't change any value is the current is the same,
the same in python module


*/


//Stepper - motor DC
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *myStepper = AFMS.getStepper(200, 2);
int stepperDirection = BACKWARD;
int stepperSpeed = 0;
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

//Servomotor
Servo myservo1, myservo2;
int servo1pin = 10;
int servo2pin = 9;
//Led strip
int rubLed1pin = 4;
//Led RGB
int ledRGBrpin = 5;
int ledRGBgpin = 6;
int ledRGBbpin = 7;
int val;

void setup(){
  
  //Stepper - motor DC
  AFMS.begin(3000);
  myMotor->setSpeed(0);
  myStepper->setSpeed(0);
  
  myservo1.attach(servo1pin);
  myservo2.attach(servo2pin);
  pinMode(rubLed1pin, OUTPUT );
  pinMode(ledRGBrpin, OUTPUT );
  pinMode(ledRGBgpin, OUTPUT ); 
  pinMode(ledRGBbpin, OUTPUT );
  Serial.begin(115200);

}

void loop(){
 
  if(Serial.available() >= 2 ){
   
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
         analogWrite(ledRGBgpin, map(val, 1, 127, 0, 255));
       break;
       case 12:
         analogWrite(ledRGBbpin, map(val, 1, 127, 0, 255));
       break;
       case 13:
         if (val > 65){
           myMotor->run(FORWARD);
           int DCSpeed = (val-65)*2;
           myMotor->setSpeed(DCSpeed);
         }
         else if(val < 61){
           myMotor->run(BACKWARD);
           int DCSpeed = abs(61-val)*2;
           myMotor->setSpeed(DCSpeed);
         }
         else{
           int DCSpeed = 0;
           myMotor->setSpeed(DCSpeed); 
          
         }
       break;
        case 14:
         if (val > 66){
           stepperSpeed = (val-63)*3;
           stepperDirection = FORWARD;
           myStepper->setSpeed(stepperSpeed);
         }
         else if(val < 60){
           stepperDirection = BACKWARD;
           stepperSpeed = abs(63-val)*3 ;
           myStepper->setSpeed(stepperSpeed);
         }
         else{
           stepperSpeed = 0;
           //myStepper->setSpeed(stepperSpeed); 
          
         }
      break;
       
     
     
     
    } 
    
    
  }
  //end of serial
  
  //Normal Loop
  if(stepperSpeed > 0 ){
      myStepper->step(1, stepperDirection, SINGLE); 
  }

}
