// Shows how to run three Steppers at once with varying speeds
//
// Requires the Adafruit_Motorshield v2 library 
//   https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library
// And AccelStepper with AFMotor support 
//   https://github.com/adafruit/AccelStepper

// This tutorial is for Adafruit Motorshield v2 only!
// Will not work with v1 shields

#include <Wire.h>
#include <AccelStepper.h>
#include <Adafruit_MotorShield.h>
#include <string.h>

//Adafruit_MotorShield AFMSbot(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers

// Connect two steppers with 200 steps per revolution (1.8 degree)
// to the top shield
Adafruit_StepperMotor *myStepper1 = AFMStop.getStepper(200, 1);
Adafruit_StepperMotor *myStepper2 = AFMStop.getStepper(200, 2);

char serial_buffer[20];
int serial_index = 0;

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep1() {  
  myStepper1->onestep(FORWARD, MICROSTEP);
}
void backwardstep1() {  
  myStepper1->onestep(BACKWARD, MICROSTEP);
}
// wrappers for the second motor!
void forwardstep2() {  
  myStepper2->onestep(FORWARD, MICROSTEP);
}
void backwardstep2() {  
  myStepper2->onestep(BACKWARD, MICROSTEP);
}
//// wrappers for the third motor!
//void forwardstep3() {  
//  myStepper3->onestep(FORWARD, INTERLEAVE);
//}
//void backwardstep3() {  
//  myStepper3->onestep(BACKWARD, INTERLEAVE);
//}

// Now we'll wrap the 3 steppers in an AccelStepper object
AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);
//AccelStepper stepper3(forwardstep3, backwardstep3);

void setup()
{  

  Serial.begin(9600);
  Serial.println("Serial started");
//  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield

  stepper1.setMaxSpeed(100000.0);
  stepper1.setAcceleration(10000.0);
  stepper2.setMaxSpeed(100000.0);
  stepper2.setAcceleration(10000.0);
}

void loop()
{
  stepper1.run();
  stepper2.run();
  handleSerial();
}

void handleSerial() {
 while (Serial.available() > 0) {
   char incomingCharacter = Serial.read();
   if(incomingCharacter == '\n'){
    serial_buffer[serial_index] = NULL;
    serial_index = 0;
    parseSerial();
   }else{
    //Serial.println(incomingCharacter);
    serial_buffer[serial_index] = incomingCharacter;
    serial_index++;
   }
 }
}

void parseSerial(){
  Serial.print("I got: ");
  char *token;
  token = strtok(serial_buffer, " ");
  String str(token);
  Serial.println(str);
  if(!strcmp(token,"m1_stop")){
    Serial.println("Stopping motor1");
    myStepper1->release();
  }else if(!strcmp(token,"m1_set_speed")){
    char *speed = strtok(NULL, " ");
    if (speed == NULL)Serial.println("No speed given!");
    stepper1.setSpeed(atof(speed));
    Serial.print("Set motor1 speed: ");
    Serial.println(stepper1.speed());
  }else if(!strcmp(token,"m1_get_speed")){
    Serial.print("Motor1 Speed: ");
    Serial.println(stepper1.speed());
  }else if(!strcmp(token, "m1_set_pos")){
    char *pos = strtok(NULL, " ");
    if (pos == NULL)Serial.println("No position given!");
    stepper1.moveTo(atof(pos));
    Serial.print("Set motor1 pos: ");
    Serial.println(stepper1.targetPosition());
  }else if(!strcmp(token,"m2_stop")){
    Serial.println("Stopping motor2");
    myStepper2->release();
  }else if(!strcmp(token,"m2_set_speed")){
    char *speed = strtok(NULL, " ");
    if (speed == NULL)Serial.println("No speed given!");
    stepper2.setSpeed(atof(speed));
    Serial.print("Set motor2 speed: ");
    Serial.println(stepper2.speed());
  }else if(!strcmp(token,"m2_get_speed")){
    Serial.print("Motor2 Speed: ");
    Serial.println(stepper2.speed());
  }else if(!strcmp(token, "m2_set_pos")){
    char *pos = strtok(NULL, " ");
    if (pos == NULL)Serial.println("No position given!");
    stepper2.moveTo(atof(pos));
    Serial.print("Set motor2 pos: ");
    Serial.println(stepper2.targetPosition());
  }else{
    Serial.println("Unknown command");
  }
}

