#include <Microduino_Key.h>
#include <Microduino_Motor.h>
 
#if defined(__AVR_ATmega32U4__) || (__AVR_ATmega1284P__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega128RFA1__)
#define motor_pin0A 8  //PWM
#define motor_pin0B 6
#define motor_pin1A 7  //PWM 
#define motor_pin1B 5
#else
#define motor_pin0A 6  //PWM
#define motor_pin0B 8
#define motor_pin1A 5  //PWM
#define motor_pin1B 7
#endif
 
Key KeyA(A6, INPUT);
Key KeyB(A6, INPUT);
Key KeyC(A6, INPUT);
Key KeyD(A6, INPUT);
Key KeyE(A6, INPUT);
 
Motor MotorLeft(motor_pin0A, motor_pin0B);
Motor MotorRight(motor_pin1A, motor_pin1B);
 
#define MAX_THROTTLE 255 //最大油门 100~255
#define MAX_STEERING 200 //最大转向 100~512
 
int16_t leftVal = 0;  //左边电机旋转速度
int16_t rightVal = 0;  //右边电机旋转速度
 
 
void setup() {
  Serial.begin(115200);  //初始化
  Serial.println("Microduino!");
 
  MotorLeft.Fix(1);
  MotorRight.Fix(1);
 
  delay(2000);
}
 
void loop() {
  switch (KeyA.read(680, 720)) {
    case SHORT_PRESS:
      Serial.println("KEY UP(analog) SHORT_PRESS");  //短按
        leftVal+=10;     //摇杆向上，旋转速度加10，最大不超过255
        if (leftVal > 255)
          leftVal = 255;
        rightVal+=10;
        if (rightVal > 255)
          rightVal = 255;
      break;
    case LONG_PRESS:
      Serial.println("KEY UP(analog) LONG_PRESS");    //长按
      break;
  }
 
  switch (KeyB.read(480, 530)) {
    case SHORT_PRESS:
      Serial.println("KEY LEFT(analog) SHORT_PRESS");  //短按
        if (leftVal > 0)     //摇杆向左，旋转方向向左
          {
            leftVal = -leftVal;
            rightVal = -rightVal;
          }
      break;
    case LONG_PRESS:
      Serial.println("KEY LEFT(analog) LONG_PRESS");    //长按
      break;
  }
 
  switch (KeyC.read(830, 870)) {
    case SHORT_PRESS:
      Serial.println("KEY RIGHT(analog) SHORT_PRESS");  //短按
        if (leftVal < 0)      //摇杆向右，旋转方向向右
          {
            leftVal = -leftVal;
            rightVal = -rightVal;
          }
      break;
    case LONG_PRESS:
      Serial.println("KEY RIGHT(analog) LONG_PRESS");    //长按
      break;
  }
 
  switch (KeyD.read(310, 350)) {
    case SHORT_PRESS:
      Serial.println("KEY DOWN(analog) SHORT_PRESS");  //短按 
        leftVal-=10;    //摇杆向下，旋转速度减10，最小不超过-255
        if (leftVal < -255)
          leftVal = -255;
        rightVal-=10;
        if (rightVal < -255)
          rightVal = -255;
      break;
    case LONG_PRESS:
      Serial.println("KEY DOWN(analog) LONG_PRESS");    //长按
      break;
  }
 
  switch (KeyE.read(0, 20)) {
    case SHORT_PRESS:
      Serial.println("KEY ENTER(analog) SHORT_PRESS");  //短按
      break;    //摇杆向下，没有定义动作
    case LONG_PRESS:
      Serial.println("KEY ENTER(analog) LONG_PRESS");    //长按
      break;
  }
 
  MotorLeft.Driver(leftVal);  //驱动电机
  MotorRight.Driver(rightVal);
  delay(15);
}
