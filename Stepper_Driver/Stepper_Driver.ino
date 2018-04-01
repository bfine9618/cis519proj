// Shows how to run three Steppers at once with varying speeds
//
// Requires the Adafruit_Motorshield v2 library 
//   https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library
// And AccelStepper with AFMotor support 
//   https://github.com/adafruit/AccelStepper

// This tutorial is for Adafruit Motorshield v2 only!
// Will not work with v1 shields

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <string.h>

Adafruit_MotorShield AFMS(0x60); // Default address, no jumpers

// Connect two steppers with 200 steps per revolution (1.8 degree)
// to the top shield
Adafruit_StepperMotor *stepper1 = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *stepper2 = AFMS.getStepper(200, 2);

void setup()
{  
  Serial.begin(9600);
  Serial.println("Serial started");
  AFMS.begin(); // Start the top shield

  // Uneccessary when using onestep
  //stepper1->setSpeed(1000);
  //stepper2->setSpeed(2000);
}

void loop()
{
  handleSerial();
}

void handleSerial() {
 while (Serial.available() > 0) {
   char incomingCharacter = Serial.read();
   switch(incomingCharacter){
    case 'r':
      stepper1->release();
      stepper2->release();
      Serial.println("Released");
      break;
    case 'a':
      stepper1->onestep(FORWARD, DOUBLE);
      break;
    case 'd':
      stepper1->onestep(BACKWARD, DOUBLE);
      break;
    case 'w':
      stepper2->onestep(FORWARD, DOUBLE);
      break;
    case 's':
      stepper2->onestep(BACKWARD, DOUBLE);
      break;
    case 'f':
      stepper1->onestep(FORWARD, MICROSTEP);
      break;
    case 'h':
      stepper1->onestep(BACKWARD, MICROSTEP);
      break;
    case 't':
      stepper2->onestep(FORWARD, MICROSTEP);
      break;
    case 'g':
      stepper2->onestep(BACKWARD, MICROSTEP);
      break;

    default:
      break;
   }
 }
}
