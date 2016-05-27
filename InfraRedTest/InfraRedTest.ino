void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}
int last  = 0;

void loop() {
  Serial.println(".......................");

  int now = digitalRead(12);
  if (now != last) {
    if (now) {
      Serial.println("++++++++++++++++++++++");
      digitalWrite(52, HIGH);
    } else {
      digitalWrite(52, LOW);
      Serial.println("-");

    }
    Serial.println(millis() / 1000);
    last = now;
  }


  delay(200);
}
