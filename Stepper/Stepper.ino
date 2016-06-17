/*
 * 步进电机跟随电位器旋转
 * (或者其他传感器)使用0号模拟口输入
 * 使用arduino IDE自带的Stepper.h库文件
 */

#include <Stepper.h>

// 这里设置步进电机旋转一圈是多少步
#define STEPS 100

// attached to设置步进电机的步数和引脚
Stepper stepper(STEPS, 8, 9, 10, 11);

void setup()
{
  Serial.begin(9600);
  // 设置电机每分钟的转速为90步
  stepper.setSpeed(90);
}


void loop()
{
  int val = 1000; //
  stepper.step(val);
  Serial.println(val);
  delay(3000);
}

