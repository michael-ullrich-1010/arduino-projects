#include <Arduino.h>
#include <steppermotor.h>

const bool print_output = true;
int output_counter = 0;

const int joyX_minus_pin = 2;
const int joyX_plus_pin = 3;
const int joyY_minus_pin = 4;
const int joyY_plus_pin = 5;

const int stepperX_limit_pin = 11;
long stepperX_counter = 0;
const long stepperX_counter_max = 98500;
const int stepperX_pulse_pin = 8;
const int stepperX_dir_pin = 9;
const int stepperX_speed = 50;

const int stepperY_limit_pin = 10;
long stepperY_counter = 0;
const long stepperY_counter_max = 37500;
const int stepperY_pulse_pin = 6;
const int stepperY_dir_pin = 7;
const int stepperY_speed = 150;

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
  stepperX.init(stepperX_pulse_pin, stepperX_dir_pin, stepperX_speed, HIGH);
  stepperX.start();

  pinMode(stepperY_limit_pin, INPUT_PULLUP);
  stepperY.init(stepperY_pulse_pin, stepperY_dir_pin, stepperY_speed, LOW);
  stepperY.start();


    // Go Home
  Serial.println("Moving to home");
  do
  {
    if (digitalRead(stepperX_limit_pin) != LOW)
    {
      stepperX.control();
    }
    if (digitalRead(stepperY_limit_pin) != LOW)
    {
      stepperY.control();
    }
  } while (digitalRead(stepperX_limit_pin) != LOW || digitalRead(stepperY_limit_pin) != LOW);

  Serial.println("Went home");

  stepperX_counter = 0;
  stepperY_counter = 0;

  Serial.println("Start");
}

void loop()
{
  if (digitalRead(stepperX_limit_pin) == LOW)
  {
    stepperX_counter = 0;
  }
  if (digitalRead(stepperY_limit_pin) == LOW)
  {
    stepperY_counter = 0;
  }

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
