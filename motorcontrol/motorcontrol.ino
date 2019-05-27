#define STEPTIME 50


class stepper {
public:
  stepper(int stepPin, int dirPin, int activeValue) {
    pinS = stepPin;
    pinD = dirPin;
    active = activeValue;
    pinMode(pinS, OUTPUT);
    pinMode(pinD, OUTPUT);
    digitalWrite(pinS, !active);
  }
  
  
  void step(int nrOfSteps) {
    if (nrOfSteps == 0)
      return;
      
    digitalWrite(pinD, (nrOfSteps > 0) ? active : !active);
    
    for (int i = 0; i < abs(nrOfSteps); ++i) {
      digitalWrite(pinS, active);
      delay(STEPTIME / 2);
      digitalWrite(pinS, !active);
      delay(STEPTIME / 2);
    }
  }

private:
  int pinS, pinD, active;
};





void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
