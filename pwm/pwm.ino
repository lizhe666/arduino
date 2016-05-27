void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  pinMode(2, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(pulseIn(2, HIGH));
  delay(1000);

}
