/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_StepperMotor *rotMotor = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *penMotor = AFMS.getStepper(200, 2);

/**
 * Initialize the motors
 */
void initMotors() {
    AFMS.begin();
    rotMotor->setSpeed(10);
    penMotor->setSpeed(10);
}

/**
 * Release the motors.
 */
void releaseMotors() {
    rotMotor->release();
    penMotor->release();
}

void setup() {
    // Initialize serial communication
    Serial.begin(9600);
    Serial.println("Eggbot!");
}

void loop() {
    initMotors();
    penMotor->step(20, FORWARD, MICROSTEP);
    delay(3000);
    rotMotor->step(20, FORWARD, MICROSTEP);
    delay(3000);
    penMotor->step(20, BACKWARD, MICROSTEP);
    delay(3000);
    rotMotor->step(20, BACKWARD, MICROSTEP);
    delay(3000);
    releaseMotors();
    delay(3000);
}
