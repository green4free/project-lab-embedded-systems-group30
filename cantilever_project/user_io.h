#pragma once

struct userInput {
  double endPoint;
  double startPoint;
  int nrOfStops;
  int nrOfSamples; 
};



void getInput(userInput* data, bool* go);

void sendData(double position, double value);
