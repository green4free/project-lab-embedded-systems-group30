#include "motorcontrol.h"
#include "user_io.h"
#include "config.h"


#include <math.h>
#include <stdio.h>


stepper motor1(9, 8, 10, 11); 

//#define REMOVE_OUTLIERS


#ifdef REMOVE_OUTLIERS
int sensorValues[NUMBER_OF_SAMPLES];
double readSensor(void) {
  
    double mean0 = 0.0;
    for (int i = 0; i < NUMBER_OF_SAMPLES; ++i) {
      sensorValues[i] = analogRead(A3);
      mean0 += ((double)sensorValues[i]) / ((double)NUMBER_OF_SAMPLES);
      
      delay(5);
    }

    double stdDiv = 0.0;

    for (int i = 0; i < NUMBER_OF_SAMPLES; ++i) {
      double tmp = ((double)sensorValues[i]) - mean0;
      stdDiv += (tmp * tmp) / ((double)NUMBER_OF_SAMPLES);
    }

    stdDiv = sqrt(stdDiv);

    
    int usedSamples = 0;

    for (int i = 0; i < NUMBER_OF_SAMPLES; ++i) {
      if (fabs(((double)sensorValues[i]) - mean0) / stdDiv < MAXIMUM_Z_SCORE) {
        ++usedSamples;
      } else {
        mean0 -= ((double)sensorValues[i]) / ((double)NUMBER_OF_SAMPLES); //Instead of adding the good values again, subtract the bad ones from the old mean
      }
    }
    
    mean0 *= ((double)NUMBER_OF_SAMPLES) / ((double)usedSamples); //And then change the divider

    return mean0 / 1024.0 * 5.0;
}

#else //REMOVE_OUTLIERS

double readSensor(void) {
  
    double mean0 = 0.0;
    for (int i = 0; i < NUMBER_OF_SAMPLES; ++i) {
      mean0 += ((double)analogRead(A3)) / ((double)NUMBER_OF_SAMPLES);
      delay(5);
    }
    
    return mean0 / 1024.0 * 5.0;
}
#endif //REMOVE_OUTLIERS


double calculateResistance(double voltage) {
    return (voltage * REFERENCE_RESISTANCE) / (5.0 - voltage);
  }


double zeroDeflectionResistance;

double resistanceToStrain(double resistance) {
  return (resistance - zeroDeflectionResistance) / resistance / FACTOR_COEFICIEN_THING;
}

double deflectionToStrain(double deflection) {
  return 0.05984 * deflection;  
}



int cantileverPosition;


void setup() {
  Serial.begin(115200);
  pinMode(A3, INPUT);
  motor1.goToBottom();
  motor1.step(ZERO_DEFELCTION_POINT);
  cantileverPosition = 0;
  delay(2000);
  zeroDeflectionResistance = calculateResistance(readSensor());
}





userInput sweepConfig;
bool startSweep = false;



void loop() {

  getInput(&sweepConfig, &startSweep);


  if (startSweep) {
    
    sweepConfig.nrOfStops += 1;//Add one to include endpoint, given value will be number of stops between start and end.
    
    int moveSize = (sweepConfig.endPoint - sweepConfig.startPoint) / (double)sweepConfig.nrOfStops * STEPS_PER_TURN * TURNS_PER_MM; //Calculate the movesize in steps, to move between the stops

    cantileverPosition += motor1.step((int)(sweepConfig.startPoint * STEPS_PER_TURN * TURNS_PER_MM) - cantileverPosition);
    delay(4000); //Wait so that the cantilever stabilises before sampling the sensor. This wait is longer than the later once as initial move to this position was probobaly longer and the cantilever might threfor be vibrating more.
    double currentP = ((double)cantileverPosition) / ((double)(STEPS_PER_TURN * TURNS_PER_MM));
    double data = calculateResistance(readSensor());
    sendData(currentP, data, deflectionToStrain(currentP / 1000.0)); //Divide position with 1000 to convert the value from mm to m when calculating strain
    
    for (int i = 0; i < sweepConfig.nrOfStops; ++i) {
      cantileverPosition += motor1.step(moveSize);
      delay(2000); 
      currentP = ((double)cantileverPosition) / ((double)(STEPS_PER_TURN * TURNS_PER_MM));
      data = calculateResistance(readSensor());
      sendData(currentP, data, deflectionToStrain(currentP / 1000.0));
    }
    
    startSweep = false;  
  }

  

  delay(3);
}
