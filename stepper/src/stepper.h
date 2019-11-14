#include <AccelStepper.h>

//Step-motor lib
#define l1motorPin1 22 // IN1 on the ULN2003 driver
#define l1motorPin2 23 // IN2 on the ULN2003 driver
#define l1motorPin3 24 // IN3 on the ULN2003 driver
#define l1motorPin4 25 // IN4 on the ULN2003 driver
#define r1motorPin1 26 // IN1 on the ULN2003 driver
#define r1motorPin2 27 // IN2 on the ULN2003 driver
#define r1motorPin3 28 // IN3 on the ULN2003 driver
#define r1motorPin4 29 // IN4 on the ULN2003 driver
#define l2motorPin1 30 // IN1 on the ULN2003 driver
#define l2motorPin2 31 // IN2 on the ULN2003 driver
#define l2motorPin3 32 // IN3 on the ULN2003 driver
#define l2motorPin4 33 // IN4 on the ULN2003 driver
#define r2motorPin1 34 // IN1 on the ULN2003 driver
#define r2motorPin2 35 // IN2 on the ULN2003 driver
#define r2motorPin3 36 // IN3 on the ULN2003 driver
#define r2motorPin4 37 // IN4 on the ULN2003 driver
#define MotorInterfaceType 8

//Step-motor setting

AccelStepper stepperl1 = AccelStepper(MotorInterfaceType, l1motorPin1, l1motorPin3, l1motorPin2, l1motorPin4);
AccelStepper stepperr1 = AccelStepper(MotorInterfaceType, r1motorPin1, r1motorPin3, r1motorPin2, r1motorPin4);
AccelStepper stepperl2 = AccelStepper(MotorInterfaceType, l2motorPin1, l2motorPin3, l2motorPin2, l2motorPin4);
AccelStepper stepperr2 = AccelStepper(MotorInterfaceType, r2motorPin1, r2motorPin3, r2motorPin2, r2motorPin4);

void forward()
{
    // Set the speed in steps per second:
    stepperl1.setSpeed(1000);
    stepperr1.setSpeed(-1000);
    stepperl2.setSpeed(1000);
    stepperr2.setSpeed(-1000);
    // Step the motor with a constant speed as set by setSpeed():
    stepperl1.runSpeed();
    stepperr1.runSpeed();
    stepperl2.runSpeed();
    stepperr2.runSpeed();
}
void backward()
{
    // Set the speed in steps per second:
    stepperl1.setSpeed(-1000);
    stepperr1.setSpeed(1000);
    stepperl2.setSpeed(-1000);
    stepperr2.setSpeed(1000);
    // Step the motor with a constant speed as set by setSpeed():
    stepperl1.runSpeed();
    stepperr1.runSpeed();
    stepperl2.runSpeed();
    stepperr2.runSpeed();
}
void stopmove()
{
    stepperl1.stop();
    stepperr1.stop();
    stepperl2.stop();
    stepperr2.stop();
}
void right90()
{
    // Set the current position to 0:
    stepperl1.setCurrentPosition(0);
    stepperr1.setCurrentPosition(0);
    stepperl2.setCurrentPosition(0);
    stepperr2.setCurrentPosition(0);
    while (stepperl1.currentPosition() != 8192)
    {
        // Set the speed in steps per second:
        stepperl1.setSpeed(1000);
        stepperr1.setSpeed(1000);
        stepperl2.setSpeed(1000);
        stepperr2.setSpeed(1000);
        // Step the motor with a constant speed as set by setSpeed():
        stepperl1.runSpeed();
        stepperr1.runSpeed();
        stepperl2.runSpeed();
        stepperr2.runSpeed();
    }
    // Set the current position to 0:
    stepperl1.setCurrentPosition(0);
    stepperr1.setCurrentPosition(0);
    stepperl2.setCurrentPosition(0);
    stepperr2.setCurrentPosition(0);
}
void left90()
{
    // Set the current position to 0:
    stepperl1.setCurrentPosition(0);
    stepperr1.setCurrentPosition(0);
    stepperl2.setCurrentPosition(0);
    stepperr2.setCurrentPosition(0);
    while (stepperl1.currentPosition() != 8192)
    {
        // Set the speed in steps per second:
        stepperl1.setSpeed(-1000);
        stepperr1.setSpeed(-1000);
        stepperl2.setSpeed(-1000);
        stepperr2.setSpeed(-1000);
        // Step the motor with a constant speed as set by setSpeed():
        stepperl1.runSpeed();
        stepperr1.runSpeed();
        stepperl2.runSpeed();
        stepperr2.runSpeed();
    }
    // Set the current position to 0:
    stepperl1.setCurrentPosition(0);
    stepperr1.setCurrentPosition(0);
    stepperl2.setCurrentPosition(0);
    stepperr2.setCurrentPosition(0);
}