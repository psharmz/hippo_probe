#include <Wire.h>
#include <FileIO.h>
#include <Servo.h>
#include <Digital_Light_TSL2561.h>
#include "DHT.h"

// Sound sensor
#define SOUND_PIN A1


int counter = 0;    // variable to store the servo position
boolean arms_raised = false; 

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

void setup() {

  // Light - it uses I2C
  Wire.begin();
  Serial.begin(9600);
  TSL2561.init();

  // Sound
  pinMode(SOUND_PIN, INPUT); 
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(90);  // starts off still
}

/*************************************************************************/ 
/**************************** LOOP ***************************************/ 
/*************************************************************************/ 

//
// Sound
//
int soundSensor() 
{
  int sensorValue = analogRead(SOUND_PIN);//use A1 to read the electrical signal
  
  Serial.print("Sound - ");
  Serial.println(sensorValue);
        
  return sensorValue;
}

//
// Light
//
long LightSensor()
{
  long lux = TSL2561.readVisibleLux();

  Serial.print("Light - ");
  Serial.println(lux);

  return lux;
}

void raise_and_lower_arms() 
{
    for (counter = 0; counter <= 46; counter += 1) { //set duration for movement
      myservo.write(135);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    arms_raised = true; 
    Serial.println("arms_raised");
    myservo.write(90);                 //stop movement 
    delay(1000); 
    for (counter = 0; counter <= 46; counter += 1) { //set duration for movement 
      myservo.write(45);              // tell servo to go to position in variable 'pos'
      delay(15);                      // waits 15ms for the servo to reach the position
    }
    Serial.println("arms_lowered"); 
    arms_raised = false;
    myservo.write(90); 
     
}


void loop() {
  
  int sound = 0;
  long light = 0;
  boolean calibrate = true; 

  //read the sensors
  sound = soundSensor();
  light = LightSensor(); 

  if (sound > 340 && light > 70) {
    Serial.println("sound detected");
    raise_and_lower_arms();
  }

  // Sleep for a while
  delay(1);   

}
