int AnalogPin = 0;              //定义analogpin为模拟口0 
int Value     = 0;
void setup()
{
  Serial.begin(9600);        //设置波特率位9600
}
void loop()
{
  while(1)
  {
    Value = analogRead( AnalogPin );
    Serial.println(Value);
    delay(200);
  }}
