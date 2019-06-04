
#pragma once




#define STEPTIME 2


class stepper {
public:
  stepper(int stepPin, int dirPin, int bottomPin); //Step and direction pins to the motor controller as well as pin to the switch detecting bottom position
  
  int step(int nrOfSteps);

  int goToBottom(void);

private:
  int pinS, pinD, pinB;
};
