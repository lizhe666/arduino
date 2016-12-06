int pin = 6;

void setup(){
  Serial.begin(9600);
  pinMode(pin, INPUT);
}

void loop(){ 
  Serial.print("  PPM Co2: ");
  unsigned long duration = pulseIn(pin, HIGH);
  Serial.print("  PPM Co2: ");
  Serial.print(duration * 2); //S8
  Serial.print("  Raw Sensor: ");
  Serial.println(duration);
  delay(1100);
}
