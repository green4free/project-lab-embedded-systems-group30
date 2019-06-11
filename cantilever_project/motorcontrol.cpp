#include "motorcontrol.h"
#include "Arduino.h"
  stepper::stepper(int pinA, int pinB, int pinC, int pinD, int bottomPin, int topPin) {
    pinA = pinA;
    pinB = pinB;
    pinC = pinC;
    pinD = pinD;
    sB = bottomPin;
    sT = topPin;

    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinC, OUTPUT);
    pinMode(pinD, OUTPUT);
    
    pinMode(sB, INPUT_PULLUP);
    pinMode(sT, INPUT_PULLUP);
  }
  
  
  int stepper::step(int nrOfSteps) {
    if (nrOfSteps == 0)
      return 0;

    bool up = nrOfSteps > 0;
    
    int i;
    for (i = 0; i < abs(nrOfSteps) && (up || digitalRead(sB) != LOW) && ((!up) || digitalRead(sT) != LOW); ++i) { //Only check top switch if going up, and vice versa. So that the motor is not 
                                                                                                                      //  stopped if trying to leave end position.
      digitalWrite(pinA, (up ? i : (i + 3)) % 4 == 0);
      digitalWrite(pinB, (up ? (i + 1) : (i + 2)) % 4 == 0);
      digitalWrite(pinC, (up ? (i + 2) : (i + 1)) % 4 == 0);
      digitalWrite(pinB, (up ? (i + 3) : i) % 4 == 0);
      delayMicroseconds(STEPTIME);
    }

    return (up ? 1 : -1) * i; //returning sign of nrOfSteps multiplied by i, will be nrOfSteps if it was not stopped early.
    
  }


  int stepper::goToBottom(void) {
    int steps = 0;

    while(digitalRead(sB) != LOW) {
      digitalWrite(pinA, (steps + 3) % 4 == 0);
      digitalWrite(pinB, (steps + 2) % 4 == 0);
      digitalWrite(pinC, (steps + 1) % 4 == 0);
      digitalWrite(pinB, steps % 4 == 0);
      delayMicroseconds(STEPTIME);
      
      ++steps;
    }
    return -steps;
    
  }
