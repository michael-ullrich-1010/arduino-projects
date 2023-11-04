#include <Arduino.h>

class greifarmAutomat{
  public:

  void goHome(axisStepper stepperX, axisStepper stepperY) {
    Serial.println("Moving to home");
    do
    {
        stepperX.goHome();
        stepperY.goHome();
    } while (!stepperX.atHome() || !stepperY.atHome());

    Serial.println("Went home");
  }
};