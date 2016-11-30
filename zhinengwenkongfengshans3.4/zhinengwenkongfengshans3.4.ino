unsigned int dutyCycle;        //占空比
unsigned int tempMin = 300;  //零速值
unsigned int tempMax = 800;  //满速值
void setup( ) {
   Serial.begin(115200);         //波特率配置串口通讯
}
void loop( ) {
   int temp= analogRead(A3);  //读取模拟值，范围：0-1023
   if (temp <= tempMin)       //低于该值电机停转
       dutyCycle = 0;
   else if (temp < tempMax)
       dutyCycle = (temp-tempMin)*255/(tempMax-tempMin);
   else    
       dutyCycle = 255;     //电机满速运转
  analogWrite(10, dutyCycle);   //产生PWM，控制电机转速
  Serial.print("Temp: ");  Serial.println(temp);
  delay(100);         // 控制刷新速度
}
