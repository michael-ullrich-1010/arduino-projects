#include <Arduino.h>

#ifndef GRIPPERMACHINE_H // include guard
#define GRIPPERMACHINE_H

#include <axisstepper.h>
#include <steppermotor.h>

class gripperMachine {
  axisStepper& stepperX;
  axisStepper& stepperY;
  stepperMotor stepperGripper;
  int gripperClose_pin;
  bool grab_item_running;

public:
  // Constructor with member initialization list

  gripperMachine(axisStepper& _stepperX, axisStepper& _stepperY) : stepperX(_stepperX), stepperY(_stepperY) {}

  void init(int _stepperGripper_pulse_pin, int _stepperGripper_dir_pin, unsigned long  _stepperGripper_speed, int _gripperClose_pin) {
    stepperGripper.init(_stepperGripper_pulse_pin, _stepperGripper_dir_pin, _stepperGripper_speed, LOW);
    gripperClose_pin = _gripperClose_pin;
    pinMode(gripperClose_pin, OUTPUT);
  }

  void grabAndHold() {
    // lowers gripper, closes gripper, and lifts gripper
    stepperGripper.changeDirection(LOW);
    for (int i = 0; i < 500; i++) {
      stepperGripper.control();
    }
    stepperGripper.changeDirection(HIGH);
    for (int i = 0; i < 500; i++) {
      stepperGripper.control();
    }
  }

  void goHome() {
    // brings gripper home
    Serial.println("Moving to home");
    Serial.print(stepperX.get_limit_pin());
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
    if (!grab_item_running) {
      grab_item_running = true;
      Serial.print("  grabItem() ");
      grabAndHold();
      //goHome();
      //release();
      grab_item_running = false;
    }
  }
};

#endif 
