void setup()
{
  Serial.begin(115200);
  pinMode(10,OUTPUT);  
}
void loop()
{
  int n=analogRead(A3);   //读取模拟口数据        
  if(n>50)     //有电压反应就运行以下程序
    digitalWrite(10,HIGH); //点亮led
  else
    digitalWrite(10,LOW); //熄灭led
  Serial.println(n);//串口监视
  delay(1000);//延时，控制刷新速率。
}
