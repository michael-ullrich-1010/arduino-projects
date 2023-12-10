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
  const bool print_output = true;

public:
  // Constructor with member initialization list

  gripperMachine(axisStepper& _stepperX, axisStepper& _stepperY) : stepperX(_stepperX), stepperY(_stepperY) {}

  void init(int _stepperGripper_pulse_pin, int _stepperGripper_dir_pin, unsigned long  _stepperGripper_speed, int _gripperClose_pin) {
    stepperGripper.init(_stepperGripper_pulse_pin, _stepperGripper_dir_pin, _stepperGripper_speed, LOW);
    stepperGripper.start();
    stepperGripper.resetSteps();
    gripperClose_pin = _gripperClose_pin;
    pinMode(gripperClose_pin, OUTPUT);
  }

  void grabAndHold() {
    // lowers gripper, closes gripper, and lifts gripper
    do {
        stepperGripper.changeDirection(HIGH);
        stepperGripper.control();
    } while (stepperGripper.steps() < 44000);
    delay(500);
    digitalWrite(gripperClose_pin, HIGH);
    do {
        stepperGripper.changeDirection(LOW);
        stepperGripper.control();
    } while (stepperGripper.steps() > 0);
    goHome();
    delay(1000);
    release();
  }

  void goHome() {
    // brings gripper home
    Serial.println("Moving to home");
    int output_counter = 0;
    do
    {
        stepperX.goHome();
        stepperY.goHome();
        if (print_output && output_counter > 500)
        {
          Serial.print(" stepperX_counter " + String(stepperX.steps()) + " " + String(stepperX.get_voltage()) + "V  ");
          Serial.print("stepperY_counter " + String(stepperY.steps()) + " " + String(stepperY.get_voltage()) + "V  ");
          Serial.println("");
          output_counter = 0;    
        }
        output_counter ++;        
    } while (!stepperX.atHome() || !stepperY.atHome());
    Serial.print("stepperX_counter " + String(stepperX.steps()) + " " + String(stepperX.get_voltage()) + "V  ");
    Serial.print("stepperY_counter " + String(stepperY.steps()) + " " + String(stepperY.get_voltage()) + "V  ");
    Serial.println("");
    Serial.println("Went home");
  }

  void release() {
    // opens gripper
    digitalWrite(gripperClose_pin, LOW);
  }

  void grabItem() {
    if (!grab_item_running) {
      grab_item_running = true;
      grabAndHold();
      //goHome();
      //release();
      grab_item_running = false;
    }
  }
};

#endif 
