#include <Pm25HardSerial.h>
Pm25HardSerial pms5003;

void setup() {
  Serial.print("In Setup");
  Serial.begin(9600);
  Serial1.begin(9600);
  //init pm2.5
  pms5003.begin(&Serial3,11);
  pms5003.sleep(false);
    
}

void loop() {
  //read the last data
  delay(600);
  pms5003.read();  //

  Serial.print("PM2.5 \t");
  Serial.println(pms5003.getLastPM25());
  
  //{"PM2.5":"","CO2":""}  将pm2.5 co2等数值，以jason的形式 通过串口1发送到上位机
  String info = "{\"PM2.5\":\"" + (String)pms5003.getLastPM25() + "\",\"CO2\":\""+ (String)400 +"\"}";
  //Serial1.write(pms5003.getLastPM25());
  Serial1.write(0x08);
  //Serial1.println(info);
}

