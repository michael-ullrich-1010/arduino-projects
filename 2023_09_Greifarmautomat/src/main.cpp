#include <Arduino.h>
#include <axisstepper.h>

const bool print_output = true;
int output_counter = 0;

const int joyX_minus_pin = 3;
const int joyX_plus_pin = 2;
const int joyY_minus_pin = 5;
const int joyY_plus_pin = 4;

const int stepperX_limit_pin = 8;
const long stepperX_counter_max = 8905;
const int stepperX_pulse_pin = 6;
const int stepperX_dir_pin = 7;
const int stepperX_speed = 100;

const int stepperY_limit_pin = 11;
const long stepperY_counter_max = 8350;
const int stepperY_pulse_pin = 9;
const int stepperY_dir_pin = 10;
const int stepperY_speed = 100;

const int gab_button_pin = 3;


axisStepper stepperX, stepperY;

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
  stepperX.init(stepperX_pulse_pin, stepperX_dir_pin, stepperX_limit_pin, stepperX_counter_max, stepperX_speed, LOW);
  stepperY.init(stepperY_pulse_pin, stepperY_dir_pin, stepperY_limit_pin, stepperY_counter_max, stepperY_speed, LOW);

  // Go Home
  Serial.println("Moving to home");
  do
  {
    stepperX.goHome();
    stepperY.goHome();
  } while (!stepperX.atHome() || !stepperY.atHome());

  Serial.println("Went home");

  stepperX.resetSteps();
  stepperY.resetSteps();

  Serial.println("Start");
}

void loop()
{
  if (digitalRead(joyX_plus_pin) == LOW)
  {
    stepperX.move(1);
  }
  if (digitalRead(joyX_minus_pin) == LOW)
  {
    stepperX.move(-1);
  }
  if (digitalRead(joyY_plus_pin) == LOW)
  {
    stepperY.move(1);
  }
  if (digitalRead(joyY_minus_pin) == LOW)
  {
    stepperY.move(-1);
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
