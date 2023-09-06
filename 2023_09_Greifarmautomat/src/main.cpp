#include <Arduino.h>
#include <AccelStepper.h>


const bool print_output = true;         


const int joyX_minus = 2;         
const int joyX_plus = 3;
const int joyY_minus = 4;         
const int joyY_plus = 5;         

const int axisX_limit = 11;
const int axisX_stepper_1 = 8;
const int axisX_stepper_2 = 9;
const int axisX_stepper_maxspeed = 5000;//2048; 4096 // stepsPerRevolution change this to fit the number of steps per revolution
const int axisX_stepper_accel = 100;         // rolePerMinute Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int axisX_stepper_step = 2000;
const int axisX_counter_max = 100;

const int axisY_limit = 10;
const int axisY_stepper_1 = 6;
const int axisY_stepper_2 = 7;
const int axisY_stepper_maxspeed = 5000;//2048; 4096 // stepsPerRevolution change this to fit the number of steps per revolution
const int axisY_stepper_accel = 100;         // rolePerMinute Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int axisY_stepper_step = 2000;
const int axisY_counter_max = 18;



int axisX_counter = 0;
int axisY_counter = 0;


AccelStepper axisX_stepper(1, axisX_stepper_1, axisX_stepper_2); // 1 = Motor shield, pins 10 and 11
AccelStepper axisY_stepper(1, axisY_stepper_1, axisY_stepper_2); // 1 = Motor shield, pins 10 and 11

void setup()
{ 
  // Joystick
  pinMode(joyX_minus, INPUT_PULLUP);  
  pinMode(joyX_plus, INPUT_PULLUP);  
  pinMode(joyY_minus, INPUT_PULLUP);  
  pinMode(joyY_plus, INPUT_PULLUP);  

  // Steppers
  pinMode(axisX_limit, INPUT_PULLUP);  
  axisX_stepper.setMaxSpeed(axisX_stepper_maxspeed);
  axisX_stepper.setAcceleration(axisX_stepper_accel);

  pinMode(axisY_limit, INPUT_PULLUP);  
  axisY_stepper.setMaxSpeed(axisY_stepper_maxspeed);
  axisY_stepper.setAcceleration(axisY_stepper_accel);

  do {
    if (digitalRead(axisX_limit) != LOW) {
      axisX_stepper.move(axisX_stepper_step);
      axisX_stepper.run();
    }
    if (digitalRead(axisY_limit) != LOW) {
      axisY_stepper.move(-axisY_stepper_step);
      axisY_stepper.run();
    }
  } while (digitalRead(axisX_limit) != LOW || digitalRead(axisY_limit) != LOW);
  
  axisX_counter = 0;
  axisY_counter = 0;

  Serial.begin(9600);

  Serial.println("Start");
}

void loop()
{
  if (digitalRead(axisX_limit) == LOW)
  {
    axisX_counter = 0;
  }
  if (digitalRead(axisY_limit) == LOW)
  {
    axisY_counter = 0;
  }

  if (digitalRead(joyX_plus) == LOW && axisX_counter < axisX_counter_max)
  {
    axisX_counter++;
    if (print_output) {
      Serial.print("joyX_plus - axisX_counter ");
      Serial.println(axisX_counter);
    }
    axisX_stepper.move(-axisY_stepper_step);
  }
  if (digitalRead(joyX_minus) == LOW && digitalRead(axisX_limit) != LOW)
  {
    axisX_counter--;
    if (print_output) {
      Serial.print("joyX_minus - axisX_counter ");
      Serial.println(axisX_counter);
    }
    axisX_stepper.move(axisX_stepper_step);
  }
  if (digitalRead(joyY_plus) == LOW && axisY_counter < axisY_counter_max)
  {
    axisY_counter++;
    if (print_output) {
      Serial.print("joyY_plus - axisY_counter ");
      Serial.println(axisY_counter);
    }
    axisY_stepper.move(axisY_stepper_step);
  }
  if (digitalRead(joyY_minus) == LOW && digitalRead(axisY_limit) != LOW)
  {
    axisY_counter--;
    if (print_output) {
      Serial.print("joyY_minus - axisY_counter ");
      Serial.println(axisY_counter);
    }
    axisY_stepper.move(-axisY_stepper_step);
  }

  axisX_stepper.run();
  axisY_stepper.run();
}
