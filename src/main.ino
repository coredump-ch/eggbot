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

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);


int incomingByte = 0;   // for incoming serial data
int parsing = 0;
int direction = 0;
int steps = 0;
char stepCountBuffer[4] = "";
unsigned int bufferLen = 0;


char readByte() {
    while (Serial.available() == 0);  // busy loop
    return Serial.read();
}

void resetParser() {
    parsing = 0;
    memset(stepCountBuffer, 0, sizeof(stepCountBuffer));
}

void initMotor() {
    AFMS.begin();
    myMotor->setSpeed(10);
}

void releaseMotor() {
    myMotor->release();
}

void setup() {
    // Initialize serial communication
    Serial.begin(9600);
    Serial.println("Eggbot!");

}

void loop() {
    incomingByte = readByte();
    Serial.print("Received ");
    Serial.println(incomingByte, DEC);
    if (!parsing) {
        if (incomingByte == 'B') {
            direction = BACKWARD;
            parsing = 1;
        } else if (incomingByte == 'F') {
            direction = FORWARD;
            parsing = 1;
        } else {
            Serial.print("Invalid direction: ");
            Serial.println(incomingByte);
        }
    } else {
        if (incomingByte >= '0' && incomingByte <= '9') {
            bufferLen = strlen(stepCountBuffer);
            if (bufferLen <= sizeof(stepCountBuffer)) {
                stepCountBuffer[bufferLen] = incomingByte;            
            } else {
                resetParser();
                Serial.println("Number too long (max 4 digits)");
            }
        } else {
            if (strlen(stepCountBuffer) == 0) {
                resetParser();
                Serial.println("Error, please provide a number of steps.");
            } else{
                steps = atoi(stepCountBuffer);
                Serial.print("Moving ");
                Serial.print(steps, DEC);
                Serial.print(" steps ");
                if (direction == FORWARD) {
                    Serial.println(" forward.");
                } else {
                    Serial.println(" backward.");
                }
                initMotor();
                myMotor->step(steps, direction, SINGLE);
                resetParser();
                releaseMotor();
            }
        }
    }
}
