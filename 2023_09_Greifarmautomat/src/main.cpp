#include <Arduino.h>
#include <steppermotor.h>

const bool print_output = true;
int output_counter = 0;

const int no_limit_triggered = LOW;
const int limit_triggered = HIGH;

const int joyX_minus_pin = 3;
const int joyX_plus_pin = 2;
const int joyY_minus_pin = 4;
const int joyY_plus_pin = 5;

const int stepperX_limit_pin = 8;
const long stepperX_counter_max = 8905;
const int stepperX_pulse_pin = 6;
const int stepperX_dir_pin = 7;
const int stepperX_speed = 100;

const int stepperY_limit_pin = 11;
const long stepperY_counter_max = 8400;
const int stepperY_pulse_pin = 9;
const int stepperY_dir_pin = 10;
const int stepperY_speed = 100;

stepperMotor stepperX, stepperY;

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
  pinMode(stepperX_limit_pin, INPUT_PULLUP);
  stepperX.init(stepperX_pulse_pin, stepperX_dir_pin, stepperX_speed, LOW);
  stepperX.start();

  pinMode(stepperY_limit_pin, INPUT_PULLUP);
  stepperY.init(stepperY_pulse_pin, stepperY_dir_pin, stepperY_speed, LOW);
  stepperY.start();


  // Go Home
  Serial.println("Moving to home");
  do
  {
    if (digitalRead(stepperX_limit_pin) == no_limit_triggered)
    {
      //stepperX.control();
    }
    if (digitalRead(stepperY_limit_pin) == no_limit_triggered)
    {
      //stepperY.control();
    }
  } while (digitalRead(stepperX_limit_pin) == no_limit_triggered || digitalRead(stepperY_limit_pin) == no_limit_triggered);

  Serial.println("Went home");

  stepperX.resetSteps();
  stepperY.resetSteps();

  Serial.println("Start");
}

void loop()
{
  if (digitalRead(stepperX_limit_pin) == limit_triggered)
  {
    stepperX.resetSteps();
  }
  if (digitalRead(stepperY_limit_pin) == limit_triggered)
  {
    stepperY.resetSteps();
  }

  int action_x = 0;
  int action_y = 0;
  if (digitalRead(joyX_plus_pin) == LOW && stepperX.steps()  < stepperX_counter_max)
  {
    action_x = 1;
  }
  if (digitalRead(joyX_minus_pin) == LOW && digitalRead(stepperX_limit_pin) == no_limit_triggered)
  {
    action_x = -1;
  }
  if (digitalRead(joyY_plus_pin) == LOW && stepperY.steps() < stepperY_counter_max)
  {
    action_y = 1;
  }
  if (digitalRead(joyY_minus_pin) == LOW && digitalRead(stepperY_limit_pin) == no_limit_triggered)
  {
    action_y = -1;
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
    Serial.print(stepperX.steps());
    Serial.print("  stepperY ");
    Serial.println(stepperY.steps());
    output_counter = 0;
  }
  output_counter ++;
}
