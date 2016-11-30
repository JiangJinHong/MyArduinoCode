unsigned int tempMin = 15;    //亮灯温度
unsigned int tempMax = 27;   //报警温度
void setup( ) {
  Serial.begin(115200);           //串口初始化
  analogReference(INTERNAL);  //调用板载1.1V基准源
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
}

void loop( ) {
   double analogVotage = 1.1*(double)analogRead(A3)/1024.0;
   double temp = 100*analogVotage; //计算温度
    unsigned int dutyCycle;     //占空比
    if (temp <= tempMin) {         //小于亮灯门限值
        dutyCycle = 0; digitalWrite(11, LOW);
      }
    else if (temp < tempMax) {   //小于报警门限
         dutyCycle = (temp-tempMin)*255/(tempMax-tempMin);
         digitalWrite(11, LOW);
       }
    else{           //发光二极管亮度最大值，并启动声音报警
          dutyCycle = 255; analogWrite(11,200);
        }
  analogWrite(10, dutyCycle); //控制发光二极管发光
  Serial.print("Temp: ");  Serial.print(temp);
  Serial.print(" Degrees    Duty cycle: ");
  Serial.println(dutyCycle);
  delay(1000); // 控制刷新速度
}
