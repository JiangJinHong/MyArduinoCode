#include <Wire.h>
 
void setup() {
  Wire.begin();        // 加入i2c总线，作为主机
  Serial.begin(9600);  
}
 
void loop() {
  Wire.requestFrom(8, 6);    // 通知8号从机上传6个字节
 
  while (Wire.available()) { 
    char c = Wire.read(); 
    Serial.print(c);         
 
  delay(500);
}}
