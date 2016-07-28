void setup() {

  Serial.begin(9600);
  Serial3.begin(9600);
  Serial.println(("BlueTooth::AT"));

  do {
    delay(200);
  } while (doATCmdWithCheck("AT\r\n", "OK", 1000) == false);

  //  doATCmd("AT+ROLE1\r\n", 1000);
  //doATCmd("AT+HELP\r\n", 3000);
  doATCmd("AT+VERSION\r\n", 1000);
  doATCmd("AT+LADDR\r\n", 1000);
  doATCmd("AT+NAME\r\n", 1000);
  doATCmd("AT+PIN\r\n", 1000);
  doATCmd("AT+BAUD\r\n", 1000);
  doATCmd("AT+STOP\r\n", 1000);
  doATCmd("AT+PARI\r\n", 1000);
  doATCmd("AT+ROLE0\r\n", 1000);
  doATCmd("AT+INQ\r\n", 20000);
  //doATCmd("AT+SHOW\r\n", 10000);



}

void loop() {
  Serial3.write(1);
  int available = Serial3.available();
  while (available > 0) {
    char c = (char) Serial3.read();
    Serial.print(c);
    available = Serial3.available();
    delay(20); //必须增加这行代码，否则数据接受不全
  }
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
