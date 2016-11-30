#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 5); //RX,TX
#define my_Serial Serial
//#define my_Serial Serial1//蓝牙使用的是串口通讯，对于mCookie-CoreUSB来说，使用的是Serial1，因此定义了串口服务。
 
 
#define PIXEL_PIN    A0    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT  6/*PIXEL_PIN:彩灯的控制引脚，用户可以自己更改控制引脚，同时也要更改硬件连接。
PIXEL_COUNT:控制灯的个数，蓝牙控制最多可以控制6个，因为App蓝牙传输数据最多写了6个。
PIXEL_PIN:彩灯的控制引脚，用户可以自己更改控制引脚，同时也要更改硬件连接。
PIXEL_COUNT:控制灯的个数，蓝牙控制最多可以控制6个，因为App蓝牙传输数据最多写了6个。*/
 
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);//该函数第一个参数控制串联灯的个数，第二个是控制用哪个pin脚输出，第三个显示颜色和变化闪烁频率
 
String currentInfo;//定义一个string对象
 
char buffer[100];//定义一个字符串数组
 
boolean buffer_sta = false;//定义一个boolean常量
 
int buffer_num = 0;//定义一个整型常量
 
int sta[4];//定义一个有4个整型常量的数组
 
boolean color_en;
 
long safe_ms = millis();//定义一个长整型常量，其中millis（）函数是Arduino语言中自有的函数，它返回以毫秒为单位的从Arduino开始执行到运行到当前的时间
 
#define val_max 255
#define val_min 0
 
void setup() {
 
  strip.begin();//调用对象strip中的函数begin（）
  strip.show(); // Initialize all pixels to 'off'
 
  // put your setup code here, to run once:
  Serial.begin(115200);// 初始化串口通信，并将波特率设置为115200
  my_Serial.begin(9600);// 蓝牙通讯的波特率（速度）为：9600，需要在setup()里面定义了串口通讯速率
 
}
 
void loop() {
  // put your main code here, to run repeatedly:
  ble();//“ble()”函数是用来接收并解析手机发送的数据，解析数据函数
  if (!color_en)//if判断语句
  {
rainbowCycle(10, 255, 0, 0, 0);/*用rainbowCycle（）函数
函数使用说明，用户可以更改自己喜欢的颜色及方式。
w：颜色渐变延时时间；
R，G，B三基色；
x：“0”表示亮度从低到高渐变，“1”表示亮度从高到底渐变。*/
 
    rainbowCycle(10, 255, 0, 0, 1);
 
    rainbowCycle(10, 0, 255, 0, 0);
    rainbowCycle(10, 0, 255, 0, 1);
 
    rainbowCycle(10, 0, 0, 255, 0);
    rainbowCycle(10, 0, 0, 255, 1);
 
    rainbowCycle(10, 255, 0, 225, 0);
    rainbowCycle(10, 255, 0, 225, 1);
 
    rainbowCycle(10, 247, 139, 5, 0);
    rainbowCycle(10, 247, 139, 5, 1);
 
    rainbowCycle(10, 255, 255, 0, 0);
    rainbowCycle(10, 255, 255, 0, 1);
 
    rainbowCycle(10, 0, 255, 255, 0);
    rainbowCycle(10, 0, 255, 255, 1);
 
    for (int i = 0; i < 3; i++)//for循环·语句
      rainbow(30);
  }
}
 
void ble()
{
  while (my_Serial.available())//while循环语句
  {
    char c = my_Serial.read();//定义一个字符常量
    delay(2);
 
    if (c == 'C')
      buffer_sta = true;// 当蓝牙连接时，会持续给BT发送“\n”的消息，只要有接收到则认为蓝牙一直在连接。并且给“color_en”赋值为真（true）
    if (c == '\n')
    {
      color_en = true;
      safe_ms = millis();
    }
    if (buffer_sta)
    {
      buffer[buffer_num] = c;
      buffer_num++;
    }
    //  Serial.println(c);//调用对象Serial的函数println（）
    //Serial.println(color_en);
  }
 
  if (buffer_sta)
  {
    buffer_sta = false;
 
    sscanf((char *)strstr((char *)buffer, "C:"), "C:%d,%d,%d,%d", &sta[0], &sta[1], &sta[2], &sta[3]);
 
    for (int a = 0; a < buffer_num; a++)
      buffer[a] = NULL;
    buffer_num = 0;
 
    for (int i = 0; i < 4; i++)
    {
      Serial.print(sta[i]);
      Serial.print(",");
    }
    Serial.println(" ");
 
    if (-1 == sta[3]) {
      colorSet(strip.Color(sta[0], sta[1], sta[2]));
    }
    else if ((0 <= sta[3]) && (sta[3] < PIXEL_COUNT)) {
      colorSet(strip.Color(sta[0], sta[1], sta[2]), sta[3]);
  }//将解析到的数据来控制灯的颜色变化，如果sta[3]的值为-1，所有连接的灯都是同一个颜色，为接收到的“sta[0], sta[1], sta[2]”组合而来的颜色，即手机上选的颜色。否则将可以单独控制6个灯的颜色。
  }
 
 if (millis() - safe_ms > 3000)//用现在millis（）函数返回的值减去之前定义的safe_ms的数值并于3000比较大小，蓝牙断开时，系统会在3S后让“color_en”的值为假（false）。开始执行自定义颜色变化，“!”表示非的意思。
 
  {
    safe_ms = millis();
    color_en = false;
  }
}
 
void colorSet(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}
 
void colorSet(uint32_t c, int i) {
  strip.setPixelColor(i, c);
  strip.show();
}
 
void rainbowCycle(uint8_t wait, int r, int g, int b, int num) {
  if (num == 0)
  {
    for (int val = 0; val < 255; val++)
    {
      ble();
      if (color_en)
        return;
      colorSet(strip.Color(map(val, val_min, val_max, 0, r), map(val, val_min, val_max, 0, g), map(val, val_min, val_max, 0, b))); //红绿蓝LED灯依次由亮到暗
 
      delay(wait);
    }
  }
  if (num == 1)
  {
    for (int val = 255; val >= 0; val--)
    {
      ble();
      if (color_en)
        return;
      colorSet(strip.Color(map(val, val_min, val_max, 0, r), map(val, val_min, val_max, 0, g), map(val, val_min, val_max, 0, b)));
      delay(wait);//延时(暂停)
    }
  }
}
 
void rainbow(uint8_t wait) {
  uint16_t i, j;
 
  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      ble();
      if (color_en)
        return;
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
