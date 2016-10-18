/*
 Fading
 
 This example shows how to fade an LED using the analogWrite() function.
 
 The circuit:
 * LED attached from digital pin 9 to ground.
 
 Created 1 Nov 2008
 By David A. Mellis
 modified 30 Aug 2011
 By Tom Igoe
 
 http://arduino.cc/en/Tutorial/Fading
 
 This example code is in the public domain.
 
 */


int ledPin[3] = { 9, 10, 11 };


void setup()  { 
  // nothing happens in setup 
} 

void loop()  { 
  for ( int i = 0 ; i<3 ; i++ ){
    for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
      // sets the value (range from 0 to 255):
      analogWrite(ledPin[i], fadeValue);         
      // wait for 30 milliseconds to see the dimming effect    
      delay(30);                            
    } 
  }

  for ( int i = 0 ; i<3 ; i++ ){
    for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
      // sets the value (range from 0 to 255):
      analogWrite(ledPin[i], fadeValue);         
      // wait for 30 milliseconds to see the dimming effect    
      delay(30);                            
    } 
  }
}


