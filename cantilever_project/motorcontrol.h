
#pragma once




#define STEPTIME 1500


class stepper {
public:
  stepper(int pinA, int pinB, int pinC, int pinD, int bottomPin, int topPin); //Step and direction pins to the motor controller as well as pins to the switchs detecting hitting the top or bottom
  
  int step(int nrOfSteps);

  int goToBottom(void);

private:
  
  int pinA, pinB, pinC, pinD, sB, sT;
};
