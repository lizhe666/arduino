void setup() {
  Serial.begin(9600);
  pinMode(22, INPUT);
  pinMode(24, INPUT);
  pinMode(26, INPUT);
  pinMode(28, INPUT);
  pinMode(30, INPUT);

}

void loop() {
  Serial.print(digitalRead(22));
  Serial.print("\t");
  Serial.print(digitalRead(24));
  Serial.print("\t");
  Serial.print(digitalRead(26));
  Serial.print("\t");
  Serial.print(digitalRead(28));
  Serial.print("\t");
  Serial.println(digitalRead(30));
  delay(200);
}
