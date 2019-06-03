#include "motorcontrol.h"
#include "config.h"


#include <math.h>
#include <stdio.h>

#define SENSE_DELAY 10

stepper motor1(8, 9, 10); 


int readSensor(int nrOfSamples) {

    int mean = 0;
    for (int i = 0; i < nrOfSamples; ++i) {
      mean += analogRead(A3);
      delay(SENSE_DELAY);
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

byte precision = 4;
char graphPrint[64];
char logPrint[64];

char vString[16], pString[16];


void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    //Serial.println(command);
    switch (command) {
      case 'R':
        cantileverPosition += motor1.step(-cantileverPosition);
        break;
        
      case 'D':
      case 'U':
        int movement = ((command == 'D') ? -1 : 1) * STEPS_PER_TURN * TURNS_PER_MM * MOVE_SIZE;
        cantileverPosition += motor1.step(movement);
        
        double currentP = cantileverPosition / (STEPS_PER_TURN * TURNS_PER_MM);
        double data = calculateValue();

        dtostrf(data, precision+3, precision, vString);
        dtostrf(currentP, precision+3, precision, pString); //The sprintf provided in arduino stdio cant handle floats, so we have to do that conversion more manualy.

        sprintf(graphPrint, "res %s", vString);
        Serial.println(graphPrint);

        sprintf(logPrint, "data x%s, y%s", pString, vString);
        Serial.println(logPrint);

        break;
      
    }
    
    while (Serial.available() > 0) //We only care about the first byte, so clear the rest
      Serial.read(); 
  }

  delay(3);
}
