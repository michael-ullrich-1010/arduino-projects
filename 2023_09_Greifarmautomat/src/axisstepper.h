#include <Arduino.h>
#include <steppermotor.h>

class axisStepper{
  stepperMotor stepper;

  public:
  
  void init(int _pulsePin, int _dirPin, int _limitPin, unsigned long _maximum, unsigned long _delayTime, bool _direction){
    // Steppers
    pinMode(_limitPin, INPUT_PULLUP);
    stepper.init(_pulsePin, _dirPin, _maximum, _direction);
    stepper.start();  
  }
  
  void move(bool _direction){
    if (digitalRead(stepperX_limit_pin) == LOW)
    {
      stepperX_counter = 0;
    }
    if (digitalRead(stepperY_limit_pin) == LOW)
    {
      stepperY_counter = 0;
    }


    stepper.changeDirection(LOW);
    stepper.control();


    int action_x = 0;
    int action_y = 0;
    if (digitalRead(joyX_plus_pin) == LOW && stepperX_counter < stepperX_counter_max)
    {
      action_x = 1;
      stepperX_counter++;
    }
    if (digitalRead(joyX_minus_pin) == LOW && digitalRead(stepperX_limit_pin) != LOW)
    {
      action_x = -1;
      stepperX_counter--;
    }
    if (digitalRead(joyY_plus_pin) == LOW && stepperY_counter < stepperY_counter_max)
    {
      action_y = 1;
      stepperY_counter++;
    }
    if (digitalRead(joyY_minus_pin) == LOW && digitalRead(stepperY_limit_pin) != LOW)
    {
      action_y = -1;
      stepperY_counter--;
    }
    
    if (action_x == -1)
    {
      stepperX.changeDirection(HIGH);
      stepperX.control();
    }
    else if (action_x == 1)
    {
      stepperX.changeDirection(LOW);
      stepperX.control();
    }
    if (action_y == -1)
    {
      stepperY.changeDirection(LOW);
      stepperY.control();
    }
    else if (action_y == 1)
    {
      stepperY.changeDirection(HIGH);
      stepperY.control();
    }

    if (print_output && output_counter > 5000)
    {
      Serial.print("stepperX_counter ");
      Serial.print(stepperX_counter);
      Serial.print("  stepperY ");
      Serial.println(stepperY_counter);
      output_counter = 0;
    }
    output_counter ++;
  }
  
  unsigned long steps(void){
    return stepCount;
  }
};
  