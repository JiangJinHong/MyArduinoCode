#include <Servo.h> 
 
//#define send
 
Servo myservo; 
int Echo = A1;  // Echo回声脚(P2.0)
int Trig =A0;  //  Trig 触发脚(P2.1)
int in1 = 5;
int in2 = 4;
int in3 = 3;
int in4 = 2;
 
int rightDistance = 0,leftDistance = 0,middleDistance = 0 ;
 
void forward()
{
 digitalWrite(in1,HIGH);
 digitalWrite(in2,LOW);
 digitalWrite(in3,HIGH);
 digitalWrite(in4,LOW);
}
 
void back()
{
 digitalWrite(in1,LOW);
 digitalWrite(in2,HIGH);
 digitalWrite(in3,LOW);
 digitalWrite(in4,HIGH);
}
 
void turnleft()
{
 digitalWrite(in1,HIGH);
 digitalWrite(in2,LOW);
 digitalWrite(in3,LOW);
 digitalWrite(in4,HIGH);
}
 
void turnright()
{
 digitalWrite(in1,LOW);
 digitalWrite(in2,HIGH);
 digitalWrite(in3,HIGH);
 digitalWrite(in4,LOW);
} 
void stop()
{
 digitalWrite(in1,LOW);
 digitalWrite(in2,LOW);
 digitalWrite(in3,LOW);
 digitalWrite(in4,LOW);
} 
 
int Distance_test()   // 量出前方距离 
{
  digitalWrite(Trig, LOW);   // 给触发脚低电平2μs
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  // 给触发脚高电平10μs，这里至少是10μs
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);    // 持续给触发脚低电
  float Fdistance = pulseIn(Echo, HIGH);  // 读取高电平时间(单位：微秒)
  Fdistance= Fdistance/58;       //为什么除以58等于厘米，  Y米=（X秒*344）/2
  // X秒=（ 2*Y米）/344 ==》X秒=0.0058*Y米 ==》厘米=微秒/58
  return (int)Fdistance;
}  
 
void setup() 
{ 
  myservo.attach(9);
  Serial.begin(9600);     // 初始化串口
  pinMode(Echo, INPUT);    // 定义超声波输入脚
  pinMode(Trig, OUTPUT);   // 定义超声波输出脚  
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
 
  stop();
} 
 
void loop() 
{ 
    myservo.write(90);
    delay(500); 
    middleDistance = Distance_test();
    #ifdef send
    Serial.print("middleDistance=");
    Serial.println(middleDistance);
    #endif
     
    if(middleDistance<=20)
    {     
      stop();
      delay(500);                         
      myservo.write(5);          
      delay(1000);      
      rightDistance = Distance_test();
 
      #ifdef send
      Serial.print("rightDistance=");
      Serial.println(rightDistance);
      #endif
       
      delay(500);
       myservo.write(90);              
      delay(1000);                                                  
      myservo.write(175);              
      delay(1000); 
      leftDistance = Distance_test();
 
      #ifdef send
      Serial.print("leftDistance=");
      Serial.println(leftDistance);
      #endif
 
      delay(500);
      myservo.write(90);              
      delay(1000);
      if(rightDistance>leftDistance)  
      {
        turnright();
        delay(450);
       }
       else if(rightDistance<leftDistance)
       {
        turnleft();
        delay(450);
       }
       else
       {
        forward();
       }
    }  
    else
      forward();                     
}
