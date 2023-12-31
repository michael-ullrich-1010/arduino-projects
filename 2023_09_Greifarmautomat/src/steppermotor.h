// https://www.tommycoolman.com/2021/07/31/control-two-independent-stepper-motors-with-an-arduino/


#ifndef STEPPERMOTOR_H // include guard
#define STEPPERMOTOR_H

#include <Arduino.h>


class stepperMotor{
  public:
     
  void stop(void){
    enable = 0;
  }
  
  void start(void){
    enable = 1;
 }
  
  
  void setSteps(unsigned long steps){
    stepCount = steps;
  }

  void resetSteps(void){
    stepCount = 0;
  }
  
  void init(int _pulsePin, int _dirPin, unsigned long _delayTime, bool _direction){
    pulsePin       = _pulsePin;
    dirPin         = _dirPin;
    delayTime      = _delayTime;
    direction      = _direction;
    step_increment = _direction == true ? 1 : -1;
    togglePulse   = LOW;
    enable        = 0;
      
    pinMode(pulsePin, OUTPUT);
    pinMode(dirPin, OUTPUT);
  }
  
  void control(void){
    currentTime = micros();
    digitalWrite(dirPin, direction);
    if(enable == 1){
      if( (currentTime - deltaTime) > delayTime ){
        pulseCount++;
 
        // Each HIGH or LOW is a "pulse"
        // But each step of the motor requires two "pulses"
        if(pulseCount % 2 == 0){
          stepCount += step_increment;
          if (stepCount < 0) {
            stepCount = 0;
          }
        }
  
        togglePulse = togglePulse == LOW ? HIGH : LOW;
        digitalWrite(pulsePin, togglePulse);
        deltaTime = currentTime;
      }
    }
  }
  
  void changeDirection(bool _direction){
    direction = _direction;
    step_increment = _direction == true ? 1 : -1;
  }
  
  unsigned long steps(void){
    return stepCount;
  }
  
  void changeSpeed(unsigned long _speed){
    delayTime = _speed;
  }
    
  private:
  unsigned long delayTime, deltaTime, currentTime;
  unsigned long pulseCount = 0;
  unsigned long stepCount = 0;
  int step_increment = 1;
  int pulsePin, dirPin;
  bool direction, togglePulse, enable;
};
  
#endif /* STEPPERMOTOR_H */
