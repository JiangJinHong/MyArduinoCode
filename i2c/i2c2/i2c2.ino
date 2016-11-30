#include <Wire.h>
 
void setup() {
  Wire.begin(8);                // 加入i2c总线，设置从机地址为#8
  Wire.onReceive(receiveEvent); // 注册接受到主机字符的事件
  Serial.begin(9600);           // 设置串口波特率
}
 
void loop() {
  delay(100);
}
 
 
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // 循环执行，直到数据包只剩下最后一个字符
    char c = Wire.read(); // 作为字符接收字节
    Serial.print(c);         //把字符打印到串口监视器中
  }
  int x = Wire.read();    // 作为整数接收字节
  Serial.println(x);         // 把整数打印到串口监视器中，并回车
}
