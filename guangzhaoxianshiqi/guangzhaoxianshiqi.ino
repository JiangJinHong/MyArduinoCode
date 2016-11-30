#include <Adafruit_NeoPixel.h> /*引用”Adafruit_NeoPixel.h”文件。引用的意思有点象“复制-粘贴”。include文件提供了一种很方便的方式共享了很多程序共有的信息。*/
#define PIN 6                         /*定义了控制LED的引脚，6表示Microduino的D6引脚，可通过Hub转接出来，用户可以更改 */
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
 //该函数第一个参数控制串联灯的个数，第二个是控制用哪个pin脚输出，第三个显示颜色和变化闪烁频率
 
#define Light_PIN A0  //光照传感器接AO引脚
 
#define Light_value1 400
#define Light_value2 800
//光强预设值，把光分为3个阶级，绿<400<蓝<800<红
 
int sensorValue;
 
void setup()                                //创建无返回值函数
 {
  Serial.begin(115200);               //初始化串口通信，并将波特率设置为115200
  strip.begin();                             //准备对灯珠进行数据发送
  strip.show();                              //初始化所有的灯珠为关的状态
}
void loop()                                  //无返回值loop函数
 {
  sensorValue = analogRead(Light_PIN);             //光检测
  Serial.println(sensorValue);                                //彩色led灯根据光强调节颜色和亮度
  if (sensorValue < Light_value1)                          //若光强小于400
colorWipe(strip.Color(0, map(sensorValue, 10, 400, 0, 255), 0));
/*“map(val,x,y,m,n)”函数为映射函数，可将某个区间的值（x-y）变幻成（m-n），val则是你需要用来映射的数据，这里是将10到400的光对应用0到25的绿光标示*/
  else if (sensorValue >= Light_value1 && sensorValue < Light_value2)
  //若光强大于400小于800
     colorWipe(strip.Color(0, 0, map(sensorValue, 400, 800, 0, 255)));
    //将400到800的光分别用0到255的蓝光表示
 else if (Light_value2 >= 800)
colorWipe(strip.Color(map(sensorValue, 800, 960, 0, 255), 0, 0));
//将800到960的光用0到255的红光表示
} 
void colorWipe(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++)  //i从0自增到LED灯个数减1
 {
    strip.setPixelColor(i, c); //将第i个灯点亮
    strip.show(); //led灯显示
  }
}
