#include "user_io.h"
#include "config.h"

#include "Arduino.h"
#include <stdlib.h>
#include <stdio.h>

char logPrint[64];

char inputBuffer[64];

void getInput(userInput* data, bool* go) {
  if (Serial.available() > 0) {
  	
  	char command = Serial.read();
  	  	
  	int i;
  	for (i = 0; Serial.available() > 0; ++i)
  		inputBuffer[i] = Serial.read();
	
	if (command == 'G') { //G for Go
		*go = true;
	} else if (command == 'S') { //S for Set
        char* readPtr = inputBuffer;
        #ifdef DEBUG
        sprintf(logPrint, "data Debug:%s", readPtr);
        Serial.println(logPrint);
        #endif
        data->endPoint = strtod(readPtr, &readPtr);
        
        if (readPtr - inputBuffer < i - 1) {
            #ifdef DEBUG
            sprintf(logPrint, "data Debug:%s", readPtr);
            Serial.println(logPrint);
            #endif
            data->startPoint = strtod(readPtr, &readPtr);
        } else {
            data->startPoint = STD_START_POINT;
        }
        
        if (readPtr - inputBuffer < i - 1) {
            #ifdef DEBUG
            sprintf(logPrint, "data Debug:%s", readPtr);
            Serial.println(logPrint);
            #endif
            data->nrOfStops = strtol(readPtr, &readPtr, 10);
            if (data->nrOfStops == 0)
                data->nrOfStops = STD_NR_STOPS;
        } else {
            data->nrOfStops = STD_NR_STOPS;
        }
        
        if (readPtr - inputBuffer < i - 1) {
            #ifdef DEBUG
            sprintf(logPrint, "data Debug:%s", readPtr);
            Serial.println(logPrint);
            #endif
            data->nrOfSamples = strtol(readPtr, &readPtr, 10);
            if (data->nrOfSamples == 0)
                data->nrOfSamples = STD_NR_SAMPLES;
        } else {
            data->nrOfSamples = STD_NR_SAMPLES;
        }

        #ifdef DEBUG
        sprintf(logPrint, "data EndDebug:%d %d", data->nrOfStops, data->nrOfSamples);
        Serial.println(logPrint);
        #endif
        
    }
  	
  }
    
  
}



char graphPrint[64];


char vString[16], pString[16];


void sendData(double position, double value) {
    dtostrf(value, SEND_PRECISION+3, SEND_PRECISION, vString);
    dtostrf(position, SEND_PRECISION+3, SEND_PRECISION, pString); //The sprintf provided in arduino stdio cant handle floats, so we have to do that conversion more manualy.

    sprintf(graphPrint, "res %s", vString);
    Serial.println(graphPrint);

    sprintf(logPrint, "data x%s, y%s", pString, vString);
    Serial.println(logPrint);

}
