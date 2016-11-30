
#include "key.h"//声明自定义的库
 
#define voice 300//声音的小的预设值，大于这个声音将被认为是噪音
 
#define mic_pin A0
#define buzzer_pin 6
#define key_pin 4
 
int voice_data;
long time, timer;
 
boolean buzzer_speak;//定义布尔型变量，布尔型数据只有两个值0和1
 
boolean add;
int i = 200;
 
void setup() {
  Serial.begin(115200);//设置波特率为115200
  pinMode(mic_pin, INPUT);//pinMode()函数用来设置引脚是输入模式还是输出模式
  pinMode(key_pin, INPUT);//定义引脚6为输入模式，用来接收信号
  pinMode(buzzer_pin, OUTPUT);//定义引脚4为输出模式
 
  key_init();
}
 
void loop() {
 
  voice_data = analogRead(mic_pin);//analogRead()函数在引脚设置为输入的情况下，可以获取引脚的电压情况HIGH（高电平）或者LOW第电平
  Serial.println(voice_data);//将数据从Arduino传递到PC，
//且单独占据一行，此数据可在串口监视器中看到
  //下面是函数的嵌套，如果声音大于预设值开始计时，计时后声音还是大，则蜂鸣器使能值为真，即开启蜂鸣器
  if (voice_data > voice)
  {
    if (millis() - time > 500 )//millis()是Arduino的自有函数，它返回以毫秒为单位的从Arduino开始执行到运行到当前的时间
    {
      voice_data = analogRead(mic_pin);
      if (voice_data > voice)
      {
        buzzer_speak = true;//蜂鸣器使能值为真，即开启蜂鸣器
        i = 200;
      }
      time = millis();
    }
  }
  else
  time = millis();
  //检查按键是否被按下，如果被按下，则蜂鸣器使能值为假，关闭蜂鸣器
  if (key_get(key_pin, 0))//调用自定义库key.h中的函数
  {
    delay(200);
    buzzer_speak = false;//蜂鸣器使能值为假，即关闭蜂鸣器
    time = millis();
  }
  if (buzzer_speak)//判断布尔型数据buzzer_speak的值
    buzzer();//调用自定义函数
  else
    noTone(buzzer_pin);//tone（)产生的声音在此结束
}
 
void buzzer()//自定义函数buzzer()
{
  if (millis() - timer > 10)
  {
    if (!add)
    {
      i++;
      if (i >= 800)
        add = true;
    }
    else
    {
      i--;
      if (i <= 200)
        add = false;
    }
    tone(buzzer_pin, i);//产生输出给压电扬声器的频率为i，前一个参数为连接到压电扬声器的数字引脚，后一个参数为以Hz为单位的频率值，
//产生的声音一直持续直到输出一个不同的声音或使用noTone(pin)函数结束在指定引脚上产生的声音
    timer = millis();
  }
}
