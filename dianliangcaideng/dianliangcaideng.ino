#include <Adafruit_NeoPixel.h>//引用头文件
#define PIN 6   /*定义了控制LED的引脚，6表示Microduino的D6引脚，可通过Hub转接出来，用户可以更改 */
#define PIN_NUM 2 //定义允许接的led灯的个数
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIN_NUM, PIN, NEO_GRB + NEO_KHZ800); //该函数第一个参数控制串联灯的个数，第二个是控制用哪个pin脚输出，第三个显示颜色和变化闪烁频率
 
//该函数第一个参数控制串联灯的个数，第二个是控制用哪个pin脚输出，第三个显示颜色和变化闪烁频率
 
void setup() //创建无返回值函数
{
  strip.begin();   //准备对灯珠进行数据发送
}
 
void loop()   //无返回值loop函数
 {
  strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
  strip.show();   //LED显示
  delay(1000);  //延迟1秒输出
  strip.setPixelColor(0, strip.Color(0, 255, 0));//绿光
  strip.show();  //LED显示
  delay(1000);  //延迟1秒输出
  strip.setPixelColor(0, strip.Color(0, 0, 255));//蓝光
  strip.show();  //LED显示
  delay(1000);  //延迟1秒输出
  strip.setPixelColor(0, strip.Color(0, 0, 0));//灭
  strip.show();  //LED显示
  delay(1000);  //延迟1秒输出
 }
