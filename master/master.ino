//D6，D8控制1A，1B的电机
#define OUT1A 6
#define OUT1B 8
//D5，D7控制2A，2B的电机
#define OUT2A 5
#define OUT2B 7
// 超声波
const int TrigPin1 = 2; //后
const int EchoPin1 = 3; 
float distance1; 
const int TrigPin2 = 0; //
const int EchoPin2 = 1; 
float distance2; 
const int TrigPin3 = 12; 
const int EchoPin3 = 13; 
float distance3; 
void left()
{
  digitalWrite(OUT1A, HIGH);
  digitalWrite(OUT1B, LOW);
  digitalWrite(OUT2A, HIGH);
  digitalWrite(OUT2B, LOW);
}
void right()
{
  digitalWrite(OUT1A, LOW);
  digitalWrite(OUT1B, HIGH);
  digitalWrite(OUT2A, LOW);
  digitalWrite(OUT2B, HIGH);
}

void back()
{
 digitalWrite(OUT1A,HIGH);
 digitalWrite(OUT1B,LOW);
 digitalWrite(OUT2A,LOW);
 digitalWrite(OUT2B,HIGH);

  }

void head()
{
 digitalWrite(OUT1A,LOW);
 digitalWrite(OUT1B,HIGH);
 digitalWrite(OUT2A,HIGH);
 digitalWrite(OUT2B,LOW);


  }

void STOP()
{
 digitalWrite(OUT1A,LOW);
 digitalWrite(OUT1B,LOW);
 digitalWrite(OUT2A,LOW);
 digitalWrite(OUT2B,LOW);


  }
/*void turnleft()
{
  analogWrite(OUT1A, fadeValue); 
  digitalWrite(OUT1B, LOW);
  analogWrite(OUT2B, fadeValue);
  digitalWrite(OUT2A, LOW);
}
 
void turnright()
{
  analogWrite(OUT2A, fadeValue); 
  digitalWrite(OUT2B, LOW);
  analogWrite(OUT1B, fadeValue);
  digitalWrite(OUT1A, LOW);
} 
void back()
{
  analogWrite(OUT1A, fadeValue); 
  digitalWrite(OUT1B, LOW);
  analogWrite(OUT2A, fadeValue);
  digitalWrite(OUT2B, LOW);
}
 
void forward()
{
  analogWrite(OUT1A, fadeValue); 
  digitalWrite(OUT1B, LOW);
  analogWrite(OUT2A, fadeValue);
  digitalWrite(OUT2B, LOW);
}
void STOP()
{
digitalWrite(OUT1A,LOW);
digitalWrite(OUT1B,LOW);  
digitalWrite(OUT2A,LOW); 
digitalWrite(OUT2B,LOW);     
}*/
void setup()
{
  pinMode(OUT1A, OUTPUT);//驱动
  pinMode(OUT1B, OUTPUT);
  pinMode(OUT2A, OUTPUT);
  pinMode(OUT2B, OUTPUT);
  
   Serial.begin(9600);  // 初始化串口通信及连接SR04的引脚
        pinMode(TrigPin1, OUTPUT);  // 要检测引脚上输入的脉冲宽度，需要先设置为输入状态
        pinMode(EchoPin1, INPUT); 
        pinMode(TrigPin2, OUTPUT); 
        pinMode(EchoPin2, INPUT); 
        pinMode(TrigPin3, OUTPUT); 
        pinMode(EchoPin3, INPUT); 
}
float  Distance_test1()
{
  // 产生一个10us的高脉冲去触发TrigPin 
        digitalWrite(TrigPin1, LOW); 
        delayMicroseconds(2); 
        digitalWrite(TrigPin1, HIGH); 
        delayMicroseconds(10);
        digitalWrite(TrigPin1, LOW); 
    // 检测脉冲宽度，并计算出距离
        distance1 = pulseIn(EchoPin1, HIGH) / 58.00;  
        return (distance1);
}
float  Distance_test2()
{
        digitalWrite(TrigPin2, LOW); 
        delayMicroseconds(2); 
        digitalWrite(TrigPin2, HIGH); 
        delayMicroseconds(10);
        digitalWrite(TrigPin2, LOW); 
        distance2 = pulseIn(EchoPin2, HIGH) / 58.00;  
        return (distance2);
}
float  Distance_test3()
{
        digitalWrite(TrigPin3, LOW); 
        delayMicroseconds(2); 
        digitalWrite(TrigPin3, HIGH); 
        delayMicroseconds(10);
        digitalWrite(TrigPin3, LOW); 
        distance3 = pulseIn(EchoPin3, HIGH) / 58.00;  
        return (distance3);
}
void loop()
{
    int t1,t2,t3;
    t1=Distance_test1();
    t2=Distance_test2();
    t3=Distance_test3();
    while((fabs(t2-t3))>4)
    {
      if (t2>t3&&(t2-t3)>4)
      { 
        right();
        delay(50);
        STOP();
        delay(250);
      }
      if (t2<t3&&fabs(t2-t3)>4)  
      {
        left();
        delay(50);
        STOP();
        delay(250);
      }
       if (t2>t3&&fabs(t2-t3)<=4)
      { 
        right();
        delay(10);
        STOP();
        delay(250);
      }
      if (t2<t3&&fabs(t2-t3)<=4)  
      {
        left();
        delay(10);
        STOP();
        delay(250);
      }
       Serial.print(t2-t3); 
        Serial.print("cm"); 
        Serial.println(); 
    t2=Distance_test2();
    t3=Distance_test3();
    }
    
}
