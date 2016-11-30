#include <IRremote.h>
#include <U8glib.h>
#define INTERVAL_LCD             20             //定义OLED刷新时间间隔  
int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long lcd_time = millis();                 //OLED刷新时间计时器
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);     //设置OLED型号  
//-------字体设置，大、中、小
#define setFont_L u8g.setFont(u8g_font_7x13)
#define setFont_M u8g.setFont(u8g_font_fixed_v0r)
#define setFont_S u8g.setFont(u8g_font_fixed_v0r)
#define setFont_SS u8g.setFont(u8g_font_fub25n)
void setup() {
    Serial.begin(9600);
    irrecv.enableIRIn(); // 启动红外解码
    Serial.println("Initialisation complete.");
}
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    u8g.firstPage();
    do {
        setFont_SS;
        u8g.setPrintPos(10, 30);
        u8g.print(results.value,HEX);
    }while( u8g.nextPage() );
    irrecv.resume();  //接收下一个值
  }
}
