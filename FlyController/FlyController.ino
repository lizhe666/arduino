//read PPM signals from 6 channels of an RC reciever
//http://arduino.cc/forum/index.php/topic,42286.0.html

//接收机两个通道分别接arduino的数字口2,3,18,19,21脚
//Most Arduino boards have two external interrupts: numbers 0 (on digital pin 2) and 1 (on digital pin 3).
//The Arduino Mega has an additional four: numbers 2 (pin 21), 3 (pin 20), 4 (pin 19), and 5 (pin 18).
int ppm0 = 2;//intrupt 0
int ppm1 = 3;//intrupt 1
int ppm2 = 21;//intrupt 2
int ppm3 = 20;//intrupt 3
int ppm4 = 19;//intrupt 4
int ppm5 = 18;//intrupt 5

unsigned long rc0_PulseStartTicks;
unsigned long rc1_PulseStartTicks;
unsigned long rc2_PulseStartTicks;
unsigned long rc3_PulseStartTicks;
unsigned long rc4_PulseStartTicks;
unsigned long rc5_PulseStartTicks;
volatile int rc0_val;
volatile int rc1_val;
volatile int rc2_val;
volatile int rc3_val;
volatile int rc4_val;
volatile int rc5_val;

void setup() {
  Serial.begin(115200);
  Serial3.begin(9600);
  do {
    delay(200);
  } while (doATCmdWithCheck("AT\r\n", "OK", 1000) == false);
  doATCmd("AT+NAME\r\n", 1000);

  //PPM inputs from RC receiver
  pinMode(ppm0, INPUT);
  pinMode(ppm1, INPUT);
  pinMode(ppm2, INPUT);
  pinMode(ppm3, INPUT);
  pinMode(ppm4, INPUT);
  pinMode(ppm5, INPUT);


  // 电平变化即触发中断
  attachInterrupt(0, rc0, CHANGE);
  attachInterrupt(1, rc1, CHANGE);
  attachInterrupt(2, rc2, CHANGE);
  attachInterrupt(3, rc3, CHANGE);
  attachInterrupt(4, rc4, CHANGE);
  attachInterrupt(5, rc5, CHANGE);
}

void rc0() {
  if (digitalRead(ppm0) == HIGH) {
    rc0_PulseStartTicks = micros();
  } else {
    rc0_val = micros() - rc0_PulseStartTicks;
  }
}
void rc1() {
  if (digitalRead(ppm1) == HIGH) {
    rc1_PulseStartTicks = micros();
  } else {
    rc1_val = micros() - rc1_PulseStartTicks;
  }
}
void rc2() {
  if (digitalRead(ppm2) == HIGH) {
    rc2_PulseStartTicks = micros();
  } else {
    rc2_val = micros() - rc2_PulseStartTicks;
  }
}
void rc3() {
  if (digitalRead( ppm3 ) == HIGH) {
    rc3_PulseStartTicks = micros();
  } else {
    rc3_val = micros() - rc3_PulseStartTicks;
  }
}
void rc4() {
  if (digitalRead( ppm4 ) == HIGH) {
    rc4_PulseStartTicks = micros();
  } else {
    rc4_val = micros() - rc4_PulseStartTicks;
  }
}
void rc5() {
  if (digitalRead( ppm5 ) == HIGH) {
    rc5_PulseStartTicks = micros();
  } else {
    rc5_val = micros() - rc5_PulseStartTicks;
  }
}

void loop() {
  //print values  //every times 22 bytes, 
  String info = String(rc0_val) + "\t" + String(rc1_val) + "\t" + String(rc2_val) + "\t" + String(rc3_val) + "\t" + String(rc4_val) + "\t" + String(rc5_val);
  Serial.println(info);
  Serial3.println(info);
  
}

/**
 * 发送AT指令，并且
 */
bool doATCmdWithCheck(String cmd, const char* check, unsigned long timeout) {
  if (true) {
    Serial.print(("BlueTooth::doATCmdWithCheck\tCHECK="));
    Serial.println(check);
    Serial.print(("\tCMD="));
    Serial.println(cmd);
  }

  while (Serial3.available() > 0) {
    Serial3.read();
    delay(2);
  }
  Serial3.setTimeout(timeout);
  Serial3.print(cmd);
  bool result = Serial3.find((char*) check);
  delay(100);//这里需要执行delay否则会导致异常
  if (true) {
    Serial.print(("\tRESULT="));
    Serial.println(result);
  }
  return result;
}

/**
 * 发送AT指令
 */
String doATCmd(String cmd, unsigned long timeout) {
  if (true) {
    Serial.print(("BlueTooth::doATCmd"));
    Serial.print(("\tCMD="));
    Serial.println(cmd);
  }

  while (Serial3.available() > 0) {
    Serial3.read();
    delay(2);
  }
  Serial3.setTimeout(timeout);
  Serial3.print(cmd);
  delay(100);//这里需要执行delay否则会导致异常
  String _data;
  int available = Serial3.available();
  /*
   * 为了这个函数，我重新定义了
   * #define SERIAL_TX_BUFFER_SIZE 512
   * #define SERIAL_RX_BUFFER_SIZE 512
   * 此文件位于   \Arduino\hardware\arduino\avr\cores\arduino
   * 切记，必须从这里修改原始文件！！！因为后面还有相关的逻辑，在这里重新定义是没有意义的
   */
  while (available > 0) {
    _data += (char) Serial3.read();
    //Serial.println(available);
    available = Serial3.available();
    delay(20); //必须增加这行代码，否则数据接受不全
  }


  if (true) {
    Serial.println(_data);
  }
  return _data;
}
