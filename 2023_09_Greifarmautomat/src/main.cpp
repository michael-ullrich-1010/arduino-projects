#include <Arduino.h>
#include <AccelStepper.h>

const bool print_output = true;

const int joyX_minus = 2;
const int joyX_plus = 3;
const int joyY_minus = 4;
const int joyY_plus = 5;

const int axisX_limit_pin = 11;
int axisX_counter = 0;
const int axisX_counter_max = 100;
const int axisX_stepper_pulse_pin = 8;
const int axisX_stepper_dir_pin = 9;
const int axisX_stepper_maxspeed = 5000; // 2048; 4096 // stepsPerRevolution change this to fit the number of steps per revolution
const int axisX_stepper_accel = 1000;    // rolePerMinute Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int axisX_stepper_step = 40;

const int axisY_limit_pin = 10;
int axisY_counter = 0;
const int axisY_counter_max = 18;
const int axisY_stepper_pulse_pin = 6;
const int axisY_stepper_dir_pin = 7;
const int axisY_stepper_maxspeed = 5000; // 2048; 4096 // stepsPerRevolution change this to fit the number of steps per revolution
const int axisY_stepper_accel = 1000;    // rolePerMinute Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int axisY_stepper_step = 40;

void setup()
{
  Serial.println("Initializing");

  // Joystick
  pinMode(joyX_minus, INPUT_PULLUP);
  pinMode(joyX_plus, INPUT_PULLUP);
  pinMode(joyY_minus, INPUT_PULLUP);
  pinMode(joyY_plus, INPUT_PULLUP);

  // Steppers
  pinMode(axisX_limit_pin, INPUT_PULLUP);
  pinMode(axisX_stepper_pulse_pin, OUTPUT);
  pinMode(axisX_stepper_dir_pin, OUTPUT);

  pinMode(axisY_limit_pin, INPUT_PULLUP);
  pinMode(axisY_stepper_pulse_pin, OUTPUT);
  pinMode(axisY_stepper_dir_pin, OUTPUT);

  // Go Home
  digitalWrite(axisX_stepper_dir_pin, HIGH);
  digitalWrite(axisY_stepper_dir_pin, HIGH);
  
  Serial.println("Moving to home");
  if (digitalRead(axisX_limit_pin) != LOW)
  {
    digitalWrite(axisX_stepper_pulse_pin, HIGH);
  }
  if (digitalRead(axisY_limit_pin) != LOW)
  {
    digitalWrite(axisY_stepper_pulse_pin, HIGH);
  }

  do
  {
    if (digitalRead(axisX_limit_pin) == LOW)
    {
      digitalWrite(axisX_stepper_pulse_pin, LOW);
    }
    if (digitalRead(axisY_limit_pin) == LOW)
    {
      digitalWrite(axisY_stepper_pulse_pin, LOW);
    }
  } while (digitalRead(axisX_limit_pin) != LOW || digitalRead(axisY_limit_pin) != LOW);

  axisX_counter = 0;
  axisY_counter = 0;

  Serial.begin(9600);

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
  if (digitalRead(joyX_plus) == LOW && axisX_counter < axisX_counter_max)
  {
    action_x = 1;
  }
  if (digitalRead(joyX_minus) == LOW && digitalRead(axisX_limit_pin) != LOW)
  {
    action_x = -1;
  }
  if (digitalRead(joyY_plus) == LOW && axisY_counter < axisY_counter_max)
  {
    action_y = 1;
  }
  if (digitalRead(joyY_minus) == LOW && digitalRead(axisY_limit_pin) != LOW)
  {
    action_y = -1;
  }
}
