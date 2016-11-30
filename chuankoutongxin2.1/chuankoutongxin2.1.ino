/*当按键状态改变时，0或1将被传入串口*/
//设置按键的引脚
const int buttonPin = 2;     
// 读取按键状态的变量
int buttonState = 0;         
void setup() {
    Serial.begin(9600); //初始化串口通信，并将波特率设置为9600
    pinMode(buttonPin, INPUT);//配置引脚的模式为输入模式
    Serial.println("Initialisation complete.");//调试信息
}
void loop() {
    buttonState = digitalRead(buttonPin);//读取按键的状态
    Serial.println(buttonState);  //将状态输出到串口
    delay(1000);    //延时一秒
}
