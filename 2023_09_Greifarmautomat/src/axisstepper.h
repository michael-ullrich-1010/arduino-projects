#include <Arduino.h>
#include <steppermotor.h>

class axisStepper{
  stepperMotor stepper;

  public:
  
  const int no_limit_triggered = LOW;
  const int limit_triggered = HIGH;

  int limit_pin = 0;
  int maximum = 0;

  void init(int _pulsePin, int _dirPin, int _limitPin, unsigned long _maximum, unsigned long _delayTime, bool _direction){
    // Steppers
    limit_pin = _limitPin;
    maximum = _maximum;
    pinMode(_limitPin, INPUT_PULLUP);
    stepper.init(_pulsePin, _dirPin, _maximum, _direction);
    stepper.start();  
  }
  
  unsigned long steps(void){
    return stepper.steps();
  }
  
  void resetSteps(void) {
    stepper.resetSteps();
  }
  
  void goHome(void) {
    if (digitalRead(limit_pin) == no_limit_triggered)
    {
      stepper.control();
    }
  }

  bool atHome(void) {
    if (digitalRead(limit_pin) == no_limit_triggered)
    {
      return false;
    }
    else
    {
      return true;
    }
  }

  void move(bool _direction){
    if (digitalRead(limit_pin) == limit_triggered)
    {
      stepper.resetSteps();
    }

    int action = 0;
    if (_direction == 1 && stepper.steps() < maximum)
    {
      action = 1;
    }
    if (_direction == -1 && digitalRead(limit_pin) == no_limit_triggered)
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
  