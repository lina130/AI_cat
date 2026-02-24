#include "TouchModule.h"
#include <Arduino.h>

// 初始化触摸模块引脚
void touchSensorInit() {
  pinMode(TOUCH_PIN, INPUT);
}

// 读取触摸状态（内置消抖，避免误触发）
bool isTouchDetected() {
  // 多次读取确认状态，消抖更稳定
  int touchState = digitalRead(TOUCH_PIN);
  delay(20); // 短延时消抖
  int touchState2 = digitalRead(TOUCH_PIN);
  
  // TTP223默认：触摸=LOW，未触摸=HIGH（若相反则改这里）
  return (touchState == LOW && touchState2 == LOW);
}