#ifndef TOUCHSENSOR_H
#define TOUCHSENSOR_H

// 触摸模块引脚定义（可在这里统一修改）
#define TOUCH_PIN 12

// 函数声明
void touchSensorInit();       // 初始化触摸模块
bool isTouchDetected();       // 读取触摸状态（返回true=触摸，false=未触摸）

#endif