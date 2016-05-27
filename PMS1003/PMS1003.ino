/**
按照PDF的说明，接正极负极两根线，以及传感器的TX输出线到Arduino板子的输入RX即可，其余的都不需要连接
UNO的板子必须先拔掉RX上的输入，然后才才能上传，上传后再插入线接收数据，  否则无法写入数据
*/
int incomeByte[32];
int data;
int z = -1;

void setup() {
  Serial.println("init...");
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
    data = Serial.read();

    //Serial.print(data, HEX);  //16进制 直接打印
    //Serial.print("|");

    if (z < 0 && data == 0x42) { //起始确认，有可能不是，得根据后续的校验
      z = 0;
    } else {
      z++;
    }
    incomeByte[z] = data;

    if (z >= 31) {
      if (incomeByte[1] != 0x4d) {
        Serial.print("01 err");
        doClean();
        return;
      }
      if (incomeByte[2] != 0x00) {
        Serial.print("02 err");
        doClean();
        return;
      }
      if (incomeByte[3] != 0x1c) {
        Serial.print("03 err");
        doClean();
        return;
      }
      //尾数校验，这个先算了, 因为前面一共有4byte 进行验证，后面有重复的概率实在是太低了，计算了验证了，可能还浪费CPU效率
      Serial.print("Pm1.0=");
      Serial.print(bytesToInt(incomeByte[10], incomeByte[11]));
      Serial.print("  Pm2.5=");
      Serial.print(bytesToInt(incomeByte[12], incomeByte[13]));
      Serial.print("  Pm10=");
      Serial.println(bytesToInt(incomeByte[14], incomeByte[15]));


      doClean();
      return;
    }
  }
}

/**
* byte数组中取int数值
*
*/
int bytesToInt(byte h, byte l) {
  int value = (int) ((l & 0xFF) | ((h << 8) & 0xFF00));
  return value;
}



//如果数据起点选择不对，则重新更
void doClean() {
  //Serial.print("doClean &z=");
  //Serial.println(z);
  z = -1;
  Serial.flush();
  data = '/0';
  for (int m = 0; m < 32; m++) {
    incomeByte[m] = 0;
  }
}
