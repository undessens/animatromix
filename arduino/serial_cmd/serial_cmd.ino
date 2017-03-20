

/*
Animatromix:
 Control stepper motor, led and servomotor remotly from 
 python script
 
 
 */

#include <Servo.h> 
#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include <utility/Adafruit_PWMServoDriver.h>

// nb_step = 400 according to the INTERLEAVE solution and type of motor
#define NB_STEP 400


//Stepper - adafruit + accstepper
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *myStepper2 = AFMS.getStepper(200, 2);
Adafruit_StepperMotor *myStepper1 = AFMS.getStepper(200, 1);
int stepperPos1 = 0;
int stepperPos2 = 0;
int initPos1 = 0;
int initPos2 = 0;
int final_speed = 0;
int final_speed2 = 0;

//Basic function used by AccelStepper library
void forwardstep1() {  
  myStepper1->onestep(FORWARD, INTERLEAVE);
}
void backwardstep1() {  
  myStepper1->onestep(BACKWARD, INTERLEAVE);
}
void forwardstep2() {  
  myStepper2->onestep(FORWARD, INTERLEAVE);
}
void backwardstep2() {  
  myStepper2->onestep(BACKWARD, INTERLEAVE);
}


//AccelStepper library : allow stepper motion not in a blocking function
AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);


// Stepper position init : hold, release, init
void holdStepper(){
 myStepper1->onestep(FORWARD, SINGLE);
 myStepper2->onestep(FORWARD, SINGLE);
 myStepper1->onestep(BACKWARD, SINGLE);
 myStepper2->onestep(BACKWARD, SINGLE);
}

// Release Stepper and avoid overheating
void releaseStepper(){
 myStepper1->release();
 myStepper2->release();
}

void initStepperPos(){
  
  initPos1 += stepperPos1; 
  initPos2 += stepperPos2;

}

//Servomotor
Servo servo1, servo2, servo3, servo4;
int servo1pin = 7;
int servo2pin = 8;
int servo3pin = 9;
int servo4pin = 10;

void releaseServo(){
 servo1.detach();
 servo2.detach();
 servo3.detach();
 servo4.detach(); 
  
}

//Led strip
int rubLed1pin = 4;
//Led RGB
int ledRGBrpin = 3;
int ledRGBgpin = 5;
int ledRGBbpin = 6;
int val;

//--------------------------------------------
//                   SETUP 
//--------------------------------------------
void setup(){

  //Stepper -  AccelStepper Library
  AFMS.begin(1500);
  //stepper1.setMaxSpeed(400.0);
  //stepper1.setAcceleration(300.0);
  //stepper1.moveTo(0);
  stepper1.setSpeed( 0.000001);
  stepper2.setSpeed( 0.000001);
    
  //stepper2.setMaxSpeed(400.0);
  //stepper2.setAcceleration(300.0);
  //stepper2.moveTo(0);
  
  //Stepper init pos
  stepperPos1 = 0;
  stepperPos2 = 0;

  //Servo
  servo1.attach(servo1pin);
  servo2.attach(servo2pin);
  servo3.attach(servo3pin);
  servo4.attach(servo4pin);
  
  //Leds
  pinMode(rubLed1pin, OUTPUT );
  pinMode(ledRGBrpin, OUTPUT );
  pinMode(ledRGBgpin, OUTPUT ); 
  pinMode(ledRGBbpin, OUTPUT );
  
  //Serial
  Serial.begin(115200);


}
//--------------------------------------------------
//                     LOOP
//--------------------------------------------------
void loop(){

  // Serial Reading
  while(Serial.available() >= 2 ){

    char id = Serial.read();
    char val = Serial.read();

    switch(id){
    case 4:
      servo1.attach(servo1pin);
      servo1.write(map(val, 0 , 127, 5, 170));
      //servo1.detach();
      break;
    case 5:
      servo2.attach(servo2pin);
      servo2.write(map(val, 0 , 127, 5, 170));
      //servo2.detach();
      break;
    case 6:
      servo3.attach(servo3pin);
      servo3.write(map(val, 0 , 127, 5, 170));
      //servo3.detach();
      break;
    case 7:
      servo4.attach(servo4pin);
      servo4.write(map(val, 0 , 127, 5, 170));
      //servo4.detach();
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
      //stepperPos1 = map(val, 1, 127, 0, NB_STEP);
      //stepperPos1 = map(val, 1, 127, 0, NB_STEP);
      final_speed = val - 63.5;
      if( abs(final_speed) < 10 ) stepper1.setSpeed( 0.0001 );
      else stepper1.setSpeed( final_speed * 3 );
      //stepper1.moveTo((stepperPos1+initPos1)); 
      break;
    case 14:
      final_speed2 = val - 63.5;
      if(abs(final_speed2) < 10 ) stepper2.setSpeed( 0.0001 );
      else stepper2.setSpeed( final_speed2 * 3 );
      
      //stepperPos2 = map(val, 1, 127, 0, NB_STEP);
      //stepper2.moveTo((stepperPos2+initPos2));
      break;
    case 20:
      holdStepper();
      break;
    case 21:
      releaseStepper();
      releaseServo();
      break;
    case 22:
      initStepperPos();
      break;




    } 


  }

  //Normal Loop
  stepper1.runSpeed();
  stepper2.runSpeed();
  


}

