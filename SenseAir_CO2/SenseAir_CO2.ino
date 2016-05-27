int pin = 10;

void setup()
{
  Serial.begin(115200);
  pinMode(pin, INPUT);
}

void loop()
{
  unsigned long duration = pulseIn(pin, HIGH, 1004);
  Serial.print("  PPM Co2: ");
  //Serial.print((duration - 2) * 2 , DEC); //S8 
  Serial.print((duration - 2) * 20 , DEC); //another 
  Serial.print("  Raw Sensor: ");
  Serial.println(duration, DEC);
  delay(1100);

}
