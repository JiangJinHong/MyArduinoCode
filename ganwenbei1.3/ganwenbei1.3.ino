#include <Adafruit_NeoPixel.h>//include声明函数
//如果对这个函数库有兴趣详情见：https://github.com/adafruit/Adafruit_NeoPixel/blob/master/Adafruit_NeoPixel.h
#include <Wire.h>//调用收发数据所使用的库函数
#include "I2Cdev.h"
 
#include <SHT2x.h>
 
#define PIXEL_PIN    A0    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT  6
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
//PIXEL_COUNT表示连的LED的数量；PIXEL_PIN表示LED灯所连的引脚； NEO_GRB + NEO_KHZ800表示显示颜色和变化闪烁频率
#define temp1    28//#define定义常量
#define temp2    30
#define temp3    32
 
float sensor_tem;//float定义基本数据单精度常量
 
void setup() {
  Serial.begin(9600);//初始化串口通信，并设置波特率9600
  Wire.begin(); 
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}
 
void loop() {
  read();//调用自定义函数
  if (sensor_tem <= temp1)//if判断语句
    colorSet(strip.Color(0, 255, 0));
    //colorSet(int color)设置颜色的函数
    //strip.Color(R,G,B)修改RGB的值可以改变所显现的颜色，R：红色；G：绿色；B：蓝色；
 
  else if (sensor_tem > temp1 && sensor_tem <= temp2)//三个逻辑运算符，>表示大于，&&表示逻辑关系“与”，<=表示大于等于
    colorSet(strip.Color(0, 0, 255));//蓝色
 
  else if (sensor_tem > temp2 && sensor_tem <= temp3)
    colorSet(strip.Color(255, 255, 0));//黄色（可参见颜色的合成规律）
 
  else
    colorSet(strip.Color(255, 0, 0));//红色
}
 
void read()
{
  sensor_tem = SHT2x.GetTemperature() ;//把获得的温度值赋给变量sensor_tem
  Serial.println(sensor_tem);//将数据从Arduino传递到PC且单独占据一行，此数据可在串口监视器中看到
  Serial.print("--");   
  Serial.println(SHT2x.GetHumidity());
  delay(100);
}
//unit32_t c表示定义灯的颜色
void colorSet(uint32_t c) {
  //for 函数循环语句
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);//i:表示第几个灯开始，从0开始算第一个灯；c 表示灯的颜色
    strip.show();//表示LED显示
    //delay(wait);
  }
}
