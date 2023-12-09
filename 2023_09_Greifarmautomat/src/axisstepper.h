#include <Arduino.h>

#ifndef AXISSTEPPER_H // include guard
#define AXISSTEPPER_H

#include <steppermotor.h>

class axisStepper{
  stepperMotor stepper;

  
  const int no_limit_triggered = LOW; //LOW;
  const int limit_triggered = HIGH;

  bool at_home;
  char name;
  int limit_pin;
  unsigned long maximum;

  bool checkForAtHome(void) {
    if (!at_home) {
      int sensorValue = analogRead(limit_pin);
      float voltage = sensorValue * (5.0 / 1023.0);
      if (voltage > 4) {
        stepper.resetSteps();
        at_home = true;
      }
    }
    return at_home;
  }

public:
  void init(char _name, int _pulsePin, int _dirPin, int _limitPin, unsigned long _maximum, unsigned long _delayTime, bool _direction){
    // Steppers
    at_home = false;
    name = _name;
    limit_pin = _limitPin;
    maximum = _maximum;
    pinMode(_limitPin, OUTPUT);
    stepper.init(_pulsePin, _dirPin, _delayTime, _direction);
    stepper.start();
  }
  
  int get_limit_pin(void){
    return limit_pin;
  }
  
  unsigned long steps(void){
    return stepper.steps();
  }
  
  void resetSteps(void) {
    stepper.resetSteps();
  }

  void goHome(void) {
    checkForAtHome();
    if (!at_home) {
      stepper.changeDirection(LOW);
      stepper.control();
    }
  }

  bool atHome(void) {
    return at_home;
  }

  void move(int _direction){
    checkForAtHome();

    int action = 0;
    if (_direction == 1 && stepper.steps() < maximum)
    {
      action = 1;
    }
    if (_direction == -1 && !at_home)
    {
      action = -1;
    }

    if (action == -1)
    {
      stepper.changeDirection(LOW);
      stepper.control();
    }
    else if (action == 1)
    {
      at_home = false;
      stepper.changeDirection(HIGH);
      stepper.control();
    }
  }
};

#endif 
