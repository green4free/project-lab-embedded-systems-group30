#include "motorcontrol.h"

  stepper::stepper(int stepPin, int dirPin, int bottomPin) {
    pinS = stepPin;
    pinD = dirPin;
    pinB = bottomPin;

    pinMode(pinS, OUTPUT);
    pinMode(pinD, OUTPUT);
    pinMode(pinB, INPUT_PULLUP);
    digitalWrite(pinS, LOW);
  }
  
  
  void stepper::step(int nrOfSteps) {
    if (nrOfSteps == 0)
      return;
      
    digitalWrite(pinD, nrOfSteps > 0);
    
    for (int i = 0; i < abs(nrOfSteps); ++i) {
      digitalWrite(pinS, HIGH);
      delay(STEPTIME / 2);
      digitalWrite(pinS, LOW);
      delay(STEPTIME / 2);
    }
  }


  int stepper::goToBottom(void) {
    digitalWrite(pinD, LOW);
    int steps = 0;

    while(digitalRead(pinB) != LOW) {
      digitalWrite(pinS, HIGH);
      delay(STEPTIME / 2);
      digitalWrite(pinS, LOW);
      delay(STEPTIME / 2);
      
      ++steps;
    }
    return steps;
    
  }
