#include <Arduino.h>
#include <steppermotor.h>

const bool print_output = true;
int output_counter = 0;

const int joyX_minus_pin = 2;
const int joyX_plus_pin = 3;
const int joyY_minus_pin = 4;
const int joyY_plus_pin = 5;

const int axisX_limit_pin = 11;
int axisX_counter = 0;
const int axisX_counter_max = 10000;
const int axisX_stepper_pulse_pin = 8;
const int axisX_stepper_dir_pin = 9;
const int axisX_stepper_maxspeed = 5000; // 2048; 4096 // stepsPerRevolution change this to fit the number of steps per revolution
const int axisX_stepper_accel = 1000;    // rolePerMinute Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int axisX_stepper_step = 40;

const int axisY_limit_pin = 10;
int axisY_counter = 0;
const int axisY_counter_max = 9500;
const int axisY_stepper_pulse_pin = 6;
const int axisY_stepper_dir_pin = 7;
const int axisY_stepper_maxspeed = 5000; // 2048; 4096 // stepsPerRevolution change this to fit the number of steps per revolution
const int axisY_stepper_accel = 1000;    // rolePerMinute Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int axisY_stepper_step = 40;


stepperMotor stepperOne, stepperTwo;

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing");

  // Joystick
  pinMode(joyX_minus_pin, INPUT_PULLUP);
  pinMode(joyX_plus_pin, INPUT_PULLUP);
  pinMode(joyY_minus_pin, INPUT_PULLUP);
  pinMode(joyY_plus_pin, INPUT_PULLUP);

  // Steppers
  pinMode(axisX_limit_pin, INPUT_PULLUP);
  stepperOne.init(axisX_stepper_pulse_pin, axisX_stepper_dir_pin, 100, HIGH);
  stepperOne.start();

  pinMode(axisY_limit_pin, INPUT_PULLUP);
  stepperTwo.init(axisY_stepper_pulse_pin, axisY_stepper_dir_pin, 100, LOW);
  stepperTwo.start();


    // Go Home
  Serial.println("Moving to home");
  do
  {

    stepperOne.control();
    stepperTwo.control();
    
    if(stepperOne.steps() == 2000){
      stepperOne.changeDirection(LOW);
      stepperOne.changeSpeed(600);
    }
    if(stepperTwo.steps() == 2000){
      stepperTwo.changeDirection(LOW);
      stepperTwo.changeSpeed(600);
    }    
  } while (digitalRead(axisX_limit_pin) != LOW || digitalRead(axisY_limit_pin) != LOW);

  Serial.println("Went home");

  axisX_counter = 0;
  axisY_counter = 0;

  Serial.println("Start");
}

void loop()
{
  if (digitalRead(axisX_limit_pin) == LOW)
  {
    axisX_counter = 0;
  }
  if (digitalRead(axisY_limit_pin) == LOW)
  {
    axisY_counter = 0;
  }

  int action_x = 0;
  int action_y = 0;
  if (digitalRead(joyX_plus_pin) == LOW && axisX_counter < axisX_counter_max)
  {
    action_x = 1;
    axisX_counter++;
  }
  if (digitalRead(joyX_minus_pin) == LOW && digitalRead(axisX_limit_pin) != LOW)
  {
    action_x = -1;
    axisX_counter--;
  }
  if (digitalRead(joyY_plus_pin) == LOW && axisY_counter < axisY_counter_max)
  {
    action_y = 1;
    axisY_counter++;
  }
  if (digitalRead(joyY_minus_pin) == LOW && digitalRead(axisY_limit_pin) != LOW)
  {
    action_y = -1;
    axisY_counter--;
  }
  
  if (print_output && output_counter > 50000)
  {
    Serial.print("axisX_counter ");
    Serial.print(axisX_counter);
    Serial.print("  axisY_counter ");
    Serial.println(axisY_counter);
    output_counter = 0;
  }
  output_counter ++;
}
