#include <Arduino.h>

class output{
  public:
  
  void init(int _threshold){
    threshold      = _threshold;
  }
  
  void print(String text){
  if (output_counter > threshold)
  {
    Serial.println(text);
    output_counter = 0;
  }
  output_counter ++;

  }
    
  private:
  unsigned long output_counter;
  unsigned long threshold;
};
  