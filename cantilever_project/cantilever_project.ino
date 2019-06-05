#include "motorcontrol.h"
#include "user_io.h"
#include "config.h"


#include <math.h>
#include <stdio.h>


stepper motor1(8, 9, 10, 11); 


int readSensor(int nrOfSamples) {

    int mean = 0;
    for (int i = 0; i < nrOfSamples; ++i) {
      mean += analogRead(A3);
    }
    return mean / nrOfSamples;

}

double g = 0;
double calculateValue() {
    return sin(++g / 7.0);
  }


int cantileverPosition;


void setup() {
  Serial.begin(115200);

  motor1.goToBottom();
  motor1.step(ZERO_DEFELCTION_POINT);
  cantileverPosition = 0;

}





userInput sweepConfig;
bool startSweep = false;



void loop() {

  getInput(&sweepConfig, &startSweep);


  if (startSweep) {
    
    sweepConfig.nrOfStops += 1; //Add one to include endpoint, given value will be number of stops between start and end. They should always be measured
    
    int moveSize = (sweepConfig.endPoint - sweepConfig.startPoint) / (double)sweepConfig.nrOfStops * STEPS_PER_TURN * TURNS_PER_MM;

    cantileverPosition += motor1.step((int)(sweepConfig.startPoint * STEPS_PER_TURN * TURNS_PER_MM) - cantileverPosition);

    double currentP = ((double)cantileverPosition) / ((double)(STEPS_PER_TURN * TURNS_PER_MM));
    double data = calculateValue();
    sendData(currentP, data);
    
    for (int i = 0; i < sweepConfig.nrOfStops; ++i) {
      cantileverPosition += motor1.step(moveSize);
      
      currentP = ((double)cantileverPosition) / ((double)(STEPS_PER_TURN * TURNS_PER_MM));
      data = calculateValue();
      sendData(currentP, data);
    }
    
    startSweep = false;  
  }

  

  delay(3);
}
