#include <Arduino.h>
#include <axisstepper.h>
#include <steppermotor.h>

class gripperMachine{
  axisStepper stepperX;
  axisStepper stepperY;
  stepperMotor stepperGripper;
  int gripperClose_pin;

  public:

  void init(axisStepper _stepperX, axisStepper _stepperY, int _stepperGripper_pulse_pin, int _stepperGripper_dir_pin, int _gripperClose_pin){
    stepperX = _stepperX;
    stepperY = _stepperY;
    stepperGripper.init(_stepperGripper_pulse_pin, _stepperGripper_dir_pin, stepperX_speed, LOW);
    gripperClose_pin = _gripperClose_pin;
  }  

  void grabAndHold() {
    // lowers gripper, closes gripper, and lifts gripper


  }

  void goHome() {
    // brings gripper home
    Serial.println("Moving to home");
    do
    {
        stepperX.goHome();
        stepperY.goHome();
    } while (!stepperX.atHome() || !stepperY.atHome());

    Serial.println("Went home");
  }

  void release() {
    // opens gripper
  }

  void grabItem() {
    grabAndHold();
    goHome();
    release();

  }
};