#include <Servo.h>//定义头文件，这里有一点要注意，可以直接在Arduino 软件菜单栏单击Sketch>Importlibrary>Servo,调用Servo 函数，也可以直接输入#include <Servo.h>，但是在输入时要注意在#include 与<Servo.h>之间要有空格，否则编译时会报错。
Servo myservo;//定义舵机变量名
void setup()
{
  Serial.begin(9600);
  myservo.attach(9);//定义舵机接口（9、10 都可以，缺点只能控制2 个）
}

void loop()
{
  myservo.write(0);//设置舵机旋转的角度
  Serial.println(0);
  delay(1000);

  myservo.write(90);//设置舵机旋转的角度
  Serial.println(90);
  delay(1000);

  myservo.write(180);//设置舵机旋转的角度
  Serial.println(180);
  delay(1000);
  
}

