// Arduino  GP2Y1051AU0F
//請不要在採樣週期裡面添加延遲delay這樣的。不然串口寄存器只有64Byte，很可能被塞滿。
int incomeByte[7];
int data;
int z = 0;

float recentData[100];
int num = 100;
int dataIndex = 0;

void setup() {
  Serial.println("init...");
  Serial.begin(2400);
}

void loop() {
  //UNO的板子必须先拔掉RX上的输入，然后才才能上传，上传后再插入线接收数据
  while (Serial.available() > 0) {
    data = Serial.read();
    //Serial.print(data, HEX);  //16进制 直接打印

    if (data == 0xaa) { //起始确认，有可能不是，得根据后续的校验
      if (z > 0) { //中间出现了 aa 这样的数据,直接抛弃这样的数据，重新开始
        z = 0;
      }
    } else {
      z++;
    }
    incomeByte[z] = data;

    if (z >= 6) {
      if (incomeByte[6] == 0xff) {
        int sum = incomeByte[1] + incomeByte[2] + incomeByte[3] + incomeByte[4];
        if (incomeByte[5] == sum) {
          //Serial.print("Data OK! |");
          showPm25();

          z = 0;
        } else { //校验位不对，重新复位
          //Serial.print("sum err");
          doClean();
		  return;
        }
      } else { //结束标志不对，复位
        //Serial.print("end err");
        doClean();
		return;
      }
    }
  }
}

//如果数据起点选择不对，则重新更
void doClean() {
  //Serial.print("doClean &z=");
  //Serial.println(z);

  z = 0;
  Serial.flush();
  data = '/0';
  for (int m = 0; m < 7; m++) {
    incomeByte[m] = 0;
  }
}

void showPm25() {
  //Serial.print(" Vo=");
  float vo = (incomeByte[1] * 256.0 + incomeByte[2]) / 1024.0 * 5.00;
  //Serial.print(vo, 3);
  //Serial.print("v | ");
  float c = vo * 700;

  //衰老算法，计算出最近  num 次的平均值
  recentData[dataIndex] = c;
  dataIndex = (dataIndex + 1) % num;

  if (dataIndex == 0) {
    float average = 0;
    for (int i = 0; i < num ; i++) {
      average += recentData[i];
    }
    average = average / num;
    Serial.print(" PM2.5 = ");
    Serial.print(average, 2);
    Serial.print("ug/m3 ");
    Serial.println();
  }
}
