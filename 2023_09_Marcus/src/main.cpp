#include <Arduino.h>
#include <steppermotor.h>

const bool print_output = true;
int output_counter = 0;

const int stepper_pulse_pin = 6;
const int stepper_dir_pin = 5;
const int stepper_speed = 500;
long stepper_counter = 0;
int stepper_inc = 1;

stepperMotor stepper;

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing");

  // Steppers
  stepper.init(stepper_pulse_pin, stepper_dir_pin, stepper_speed, LOW);
  stepper.start();

  Serial.println("Start");
}

void loop()
{ 
  stepper.control();
  stepper_counter += stepper_inc;

  if(stepper_counter > 30000){
    stepper.changeDirection(HIGH);
    stepper_inc = -1;
    stepper_counter = 30000;
    delay(7500+random(5000));
  }
  else if(stepper_counter < 0){
    stepper.changeDirection(LOW);
    stepper_inc = 1;
  }  
  if (print_output && output_counter > 5000)
  {
    Serial.print("stepper_counter ");
    Serial.print(stepper_counter);
    Serial.print("   ");
    Serial.println(stepper.steps());
    output_counter = 0;
  }
  output_counter ++;
}
