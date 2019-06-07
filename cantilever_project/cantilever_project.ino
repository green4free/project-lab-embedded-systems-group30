#include "motorcontrol.h"
#include "user_io.h"
#include "config.h"


#include <math.h>
#include <stdio.h>


stepper motor1(8, 9, 10, 11); 


double readSensor(int nrOfSamples) {

    double mean = 0.0;
    for (int i = 0; i < nrOfSamples; ++i) {
      mean += ((double)analogRead(A3)) / ((double)nrOfSamples);
      delay(5);
    }
    return mean / 1024.0 * 5.0; //Mean voltage

}


double calculateResistance(double voltage) {
    return (voltage * REFERENCE_RESISTANCE) / (5.0 - voltage);
  }


double zeroDeflectionResistance;

double resistanceToStrain(double resistance) {
  return (resistance - zeroDeflectionResistance) / resistance / FACTOR_COEFICIEN_THING;
}





int cantileverPosition;


void setup() {
  Serial.begin(115200);
  pinMode(A3, INPUT);
  motor1.goToBottom();
  motor1.step(ZERO_DEFELCTION_POINT);
  cantileverPosition = 0;
  delay(2000);
  zeroDeflectionResistance = calculateResistance(readSensor(500));
}





userInput sweepConfig;
bool startSweep = false;



void loop() {

  getInput(&sweepConfig, &startSweep);


  if (startSweep) {
    
    sweepConfig.nrOfStops += 1; //Add one to include endpoint, given value will be number of stops between start and end. They should always be measured
    
    int moveSize = (sweepConfig.endPoint - sweepConfig.startPoint) / (double)sweepConfig.nrOfStops * STEPS_PER_TURN * TURNS_PER_MM;

    cantileverPosition += motor1.step((int)(sweepConfig.startPoint * STEPS_PER_TURN * TURNS_PER_MM) - cantileverPosition);
    delay(4000);
    double currentP = ((double)cantileverPosition) / ((double)(STEPS_PER_TURN * TURNS_PER_MM));
    double data = calculateResistance(readSensor(sweepConfig.nrOfSamples));
    sendData(currentP, data);
    
    for (int i = 0; i < sweepConfig.nrOfStops; ++i) {
      cantileverPosition += motor1.step(moveSize);
      delay(2000); 
      currentP = ((double)cantileverPosition) / ((double)(STEPS_PER_TURN * TURNS_PER_MM));
      data = calculateResistance(readSensor(sweepConfig.nrOfSamples));
      sendData(currentP, data);
    }
    
    startSweep = false;  
  }

  

  delay(3);
}
