void setup() {

  pinMode(2, OUTPUT); //设置引脚为输出引脚
  pinMode(3, OUTPUT); //设置引脚为输出引脚
  pinMode(5, OUTPUT); //设置引脚为输出引脚
  pinMode(6, OUTPUT); //设置引脚为输出引脚
  pinMode(9, OUTPUT); //设置引脚为输出引脚
  pinMode(10, OUTPUT); //设置引脚为输出引脚
  pinMode(11, OUTPUT); //设置引脚为输出引脚


}

void loop() {
  // put your main code here, to run repeatedly:
// 默认全部断开 ， 是 24.1 V 左右  风扇转速很温和  
  digitalWrite(2, LOW);
  
  analogWrite(3, 40);   //46.5   V
  analogWrite(5, 30);    //
  analogWrite(6, 20);     //48
  analogWrite(9, 10);     //45.75
  analogWrite(10, 5);    //42.95
  analogWrite(11, 3);    //
  
  //analogWrite(3, 128);   //46.5   V
  //analogWrite(5, 100);    //
  //analogWrite(6, 90);     //48
  //analogWrite(9, 80);     //45.75
  //analogWrite(10, 64);    //42.95
  //analogWrite(11, 32);    //
  
  delay(1000);
}
