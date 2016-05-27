void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(1));
  
  //如果纯水，全覆盖，大概是530多。  用400多做为上线比较靠谱，然后水位低到120以下开始加水
  
}
