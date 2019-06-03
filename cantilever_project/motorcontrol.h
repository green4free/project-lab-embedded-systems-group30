
#pragma once
#include "Arduino.h"



#define STEPTIME 2


class stepper {
public:
  stepper(int stepPin, int dirPin, int bottomPin);  
  
  void step(int nrOfSteps);

  int goToBottom(void);

private:
  int pinS, pinD, pinB;
};
