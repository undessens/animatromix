

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

/* TODO 
Refactor + info
 */


//Stepper - adafruit + accstepper
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *myStepper2 = AFMS.getStepper(200, 2);
Adafruit_StepperMotor *myStepper1 = AFMS.getStepper(200, 1);
int stepperPos1 = 0;
int stepperPos2 = 0;
int initPos1 = 0;
int initPos2 = 0;

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





AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);


void holdStepper(){
 myStepper1->onestep(FORWARD, SINGLE);
 myStepper2->onestep(FORWARD, SINGLE);
 myStepper1->onestep(BACKWARD, SINGLE);
 myStepper2->onestep(BACKWARD, SINGLE);
}

void releaseStepper(){
 myStepper1->release();
 myStepper2->release();
}

void initStepperPos(){
  
  initPos1 += stepperPos1; 
  initPos2 += stepperPos2;
  //stepperPos1 = 0;
  //stepperPos2 = 0;
  //stepper1.move(stepperPos1-initPos1);
  //stepper2.move(stepperPos2-initPos2);
}

//Servomotor
Servo myservo1, myservo2;
int servo1pin = 9;
int servo2pin = 10;
//Led strip
int rubLed1pin = 4;
//Led RGB
int ledRGBrpin = 3;
int ledRGBgpin = 5;
int ledRGBbpin = 6;
int val;

void setup(){

  //Stepper - motor DC
  //AFMS.begin();
  AFMS.begin(1500);
  stepper1.setMaxSpeed(400.0);
  stepper1.setAcceleration(300.0);
  stepper1.moveTo(0);
    
  stepper2.setMaxSpeed(400.0);
  stepper2.setAcceleration(300.0);
  stepper2.moveTo(0);
  stepperPos1 = 0;
  stepperPos2 = 0;

  myservo1.attach(servo1pin);
  myservo2.attach(servo2pin);
  pinMode(rubLed1pin, OUTPUT );
  pinMode(ledRGBrpin, OUTPUT );
  pinMode(ledRGBgpin, OUTPUT ); 
  pinMode(ledRGBbpin, OUTPUT );
  Serial.begin(115200);


}

void loop(){

  while(Serial.available() >= 2 ){

    char id = Serial.read();
    char val = Serial.read();

    switch(id){
    case 7:
      myServo1.write(map(val, 0 , 127, 0, 180));
      break;
    case 4:
      myServo2.write(map(val, 0 , 127, 0, 180));
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
      stepperPos1 = map(val, 1, 127, 0, NB_STEP);
      stepper1.moveTo((stepperPos1+initPos1)); 
      break;
    case 14:
      stepperPos2 = map(val, 1, 127, 0, NB_STEP);
      stepper2.moveTo((stepperPos2+initPos2));
      break;
  case 20:
      holdStepper();
      break;
  case 21:
      releaseStepper();
      break;
  case 22:
      initStepperPos();
      break;




    } 


  }
  //end of serial

  //Normal Loop
  stepper1.run();
  stepper2.run();
  


}

