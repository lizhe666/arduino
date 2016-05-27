#include <VOC_MS1100_P211.h> 

VOC_MS1100_P211 sensor(3);
 
void setup() {
    //5V+
    Serial.begin(9600);
    Serial.println("Initing...");
    

}
 
void loop() {
  Serial.print("VOC=");  
  Serial.println(sensor.read(true));
  delay(200);
}
