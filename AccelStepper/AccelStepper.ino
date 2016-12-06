#include "AccelStepper.h"
// Define a stepper and the pins it will use
AccelStepper stepper(1, 9, 8);
int pos = 36000;
void setup(){  
  Serial.begin(9600);
  Serial.println("begin");
  delay(2000);
  stepper.setMaxSpeed(9000);
  stepper.setAcceleration(3000);
}

void loop(){
  if (stepper.distanceToGo() == 0){
    delay(500);
    pos = -pos;
    stepper.moveTo(pos);
  }
  stepper.run();
}
