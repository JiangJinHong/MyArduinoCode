#include <Microduino_Key.h>
#include <Servo.h>
 
Servo myservo;
 
#define servo_pin SDA
 
int pose=5, angle = 90;  //舵机旋转精度和角度
int angleCache = 0;   //角度缓存变量
 
Key KeyA(A0, INPUT);     //定义摇杆输入，可自定义端口，但是一定要注意base板上插的端口一定要和代码对应
Key KeyB(A0, INPUT);
Key KeyC(A0, INPUT);
Key KeyD(A0, INPUT);
Key KeyE(A0, INPUT);
 
void setup() {
  Serial.begin(115200);    
  Serial.println("Microduino!");
  myservo.attach(servo_pin);   //初始化
}
 
void loop() {
  //摇杆向上
  switch (KeyA.read(680, 720)) {
    case SHORT_PRESS:
      Serial.println("KEY UP(analog) SHORT_PRESS");  //短按
        pose++;     //精度加1，不超过10
        if (pose > 10)
        pose = 10;         
      break;
    case LONG_PRESS:
      Serial.println("KEY UP(analog) LONG_PRESS");    //长按
      break;
  }
 
  //摇杆向左
  switch (KeyB.read(480, 530)) {
    case SHORT_PRESS:
      Serial.println("KEY LEFT(analog) SHORT_PRESS");  //短按
        angle += pose;  //角度增加，最大不超过180度，精度为pose值，
        if (angle > 180)
        angle = 180;        
      break;
    case LONG_PRESS:
      Serial.println("KEY LEFT(analog) LONG_PRESS");    //长按
      break;
  }
 
 
  //摇杆向右
  switch (KeyC.read(830, 870)) {
    case SHORT_PRESS:
      Serial.println("KEY RIGHT(analog) SHORT_PRESS");  //短按
        angle -= pose;  //角度减少，最小不超过0度，精度为pose值，
        if (angle < 0)
        angle = 0;         
      break;
    case LONG_PRESS:
      Serial.println("KEY RIGHT(analog) LONG_PRESS");    //长按
      break;
  }
 
 
  //摇杆向下
  switch (KeyD.read(310, 350)) {
    case SHORT_PRESS:
      Serial.println("KEY DOWN(analog) SHORT_PRESS");  //短按
        pose--;    //精度减1，不低于1
        if (pose < 1)
        pose = 1;              
      break;
    case LONG_PRESS:
      Serial.println("KEY DOWN(analog) LONG_PRESS");    //长按
      break;
  }
 
 
  //摇杆向里按
  switch (KeyE.read(0, 20)) {
    case SHORT_PRESS:
      Serial.println("KEY ENTER(analog) SHORT_PRESS");  //短按
      break;
    case LONG_PRESS:
      Serial.println("KEY ENTER(analog) LONG_PRESS");    //长按
      break;
  }
 
 
  if (angleCache != angle)
  {
    myservo.write(angle);  //舵机使动函数
    angleCache=angle;
  }
 
  delay(15);
}
