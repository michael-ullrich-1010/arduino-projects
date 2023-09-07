#include <Arduino.h>

const bool print_output = true;

const int joyX_minus_pin = 2;
const int joyX_plus_pin = 3;
const int joyY_minus_pin = 4;
const int joyY_plus_pin = 5;

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

bool went_home = false;

void stepper_x_move(int action_x)
{
  if (action_x == 1) {digitalWrite(axisX_stepper_dir_pin, HIGH);}
  else if (action_x == -1) {digitalWrite(axisX_stepper_dir_pin, LOW);}
  if (action_x != 0)
  {
    digitalWrite(axisX_stepper_pulse_pin, HIGH);
    delayMicroseconds(200);   
    digitalWrite(axisX_stepper_pulse_pin, LOW);
  }
}

void stepper_y_move(int action_y)
{
  if (action_y == 1) {digitalWrite(axisY_stepper_dir_pin, HIGH);}
  else if (action_y == -1) {digitalWrite(axisY_stepper_dir_pin, LOW);}
  if (action_y != 0)
  {
    digitalWrite(axisY_stepper_pulse_pin, HIGH);
    delayMicroseconds(200);   
    digitalWrite(axisY_stepper_pulse_pin, LOW);
  }
}

void go_home()
{
  if (went_home == false)
  {
    Serial.println("Moving to home");

    went_home = true;
  }
}

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
  pinMode(axisX_stepper_pulse_pin, OUTPUT);
  pinMode(axisX_stepper_dir_pin, OUTPUT);

  pinMode(axisY_limit_pin, INPUT_PULLUP);
  pinMode(axisY_stepper_pulse_pin, OUTPUT);
  pinMode(axisY_stepper_dir_pin, OUTPUT);

  // Go Home
  Serial.println("Moving to home");
  do
  {
    if (digitalRead(axisX_limit_pin) != LOW)
    {
      stepper_x_move(true);
    }
    if (digitalRead(axisY_limit_pin) != LOW)
    {
      stepper_y_move(false);
    }
    //delayMicroseconds(800);   
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
  }
  if (digitalRead(joyX_minus_pin) == LOW && digitalRead(axisX_limit_pin) != LOW)
  {
    action_x = -1;
  }
  if (digitalRead(joyY_plus_pin) == LOW && axisY_counter < axisY_counter_max)
  {
    action_y = 1;
  }
  if (digitalRead(joyY_minus_pin) == LOW && digitalRead(axisY_limit_pin) != LOW)
  {
    action_y = -1;
  }

  stepper_x_move(action_x);
  stepper_y_move(action_y);
  
}
