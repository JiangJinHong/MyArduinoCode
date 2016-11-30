double analogVotage;  //模拟电压值
double temp;          //温度
unsigned int dutyCycle;  //占空比
unsigned int tempMin = 25;  //零速温度，设为串口观察到的环境温度
unsigned int tempMax = 35;  //满速温度，设为串口观察到的手握元件温度
void setup() {
  Serial.begin(115200);      //设置串口波特率
  analogReference(INTERNAL);  //调用板载1.1V基准源
}
void loop() {
  analogVotage = 1.1*(float)analogRead(A3)/1024;   //把ADC读取值换算成电压
  temp = 100*analogVotage;      //电压换算成温度
  if (temp < tempMin){
      dutyCycle = 0;
      }
  else if (temp < tempMax){
      dutyCycle = (temp-tempMin)*255/(tempMax-tempMin);
      }
  else {
      dutyCycle = 255;
      }
  analogWrite(10,dutyCycle);  //产生PWM
  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" Degrees    Duty cycle: ");
  Serial.println(dutyCycle);
  delay(1000);    //等待0.1秒，控制刷新速度
}
