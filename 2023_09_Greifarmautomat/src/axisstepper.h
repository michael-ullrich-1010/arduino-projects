#include <Arduino.h>

#ifndef AXISSTEPPER_H // include guard
#define AXISSTEPPER_H

#include <steppermotor.h>

class axisStepper{
  stepperMotor stepper;

  String name;
  int limit_pin;
  unsigned long maximum;

  bool checkForAtHome(void) {
    if (get_voltage() > 4.5) {
      stepper.resetSteps();
      return true;
    }
    else {
      return false;
    }
  }

public:
  void init(String _name, int _pulsePin, int _dirPin, int _limitPin, unsigned long _maximum, unsigned long _delayTime, bool _direction){
    name = _name;
    limit_pin = _limitPin;
    maximum = _maximum;
    pinMode(_limitPin, INPUT);
    stepper.init(_pulsePin, _dirPin, _delayTime, _direction);
    stepper.start();
    stepper.resetSteps();
  }
  
  int get_limit_pin(void){
    return limit_pin;
  }
  
  unsigned long steps(void){
    return stepper.steps();
  }
  
  float get_voltage(void){
    int sensorValue = analogRead(limit_pin);
    float voltage = sensorValue * (5.0 / 1023.0);    
    return voltage;
  }
  
  void resetSteps(void) {
    stepper.resetSteps();
  }

  void goHome(void) {
    bool at_home = checkForAtHome();
    if (!at_home) {
      stepper.changeDirection(LOW);
      stepper.control();
    }
  }

  bool atHome(void) {
    return checkForAtHome();
  }

  void move(int _direction){
    bool at_home = checkForAtHome();
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
      stepper.changeDirection(HIGH);
      stepper.control();
    }
  }
};

#endif // AXISSTEPPER_H
