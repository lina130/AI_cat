#include "tft_screen.h"

TFT_eSPI tft = TFT_eSPI();


void tft_screen_init() {
  // 1. 先配置所有引脚为输出
  pinMode(TFT_CS1, OUTPUT);
  pinMode(TFT_CS2, OUTPUT);
  pinMode(TFT_DC, OUTPUT); // 明确初始化DC引脚（避免遗漏）
  
  // 2. 先选中屏1，再初始化TFT_eSPI
  digitalWrite(TFT_CS2, LOW);
  digitalWrite(TFT_CS1, LOW);
  delay(20);
  
  // 3. 执行TFT初始化
  tft.init();                
  tft.setRotation(0);        
  
  // 4. 初始化后取消所有CS选中
  digitalWrite(TFT_CS1, HIGH);
  digitalWrite(TFT_CS2, HIGH);
  delay(10);
}

void tft_select_screen1() {
  digitalWrite(TFT_CS2, HIGH); 
  delay(10);                   
  digitalWrite(TFT_CS1, LOW); 
  delay(20);                  
}


void tft_select_screen2() {
  digitalWrite(TFT_CS1, HIGH); 
  delay(10);                   
  digitalWrite(TFT_CS2, LOW);  
  delay(30);                  
}


void tft_screen_draw_eye1_on() {
  tft_select_screen1(); 
  tft.fillScreen(TFT_BLACK); 
  tft.drawChar(80, 90, '~', TFT_WHITE, TFT_BLACK, 20);
  digitalWrite(TFT_CS1, HIGH); 
  delay(5);
}
void tft_screen_draw_eye1_off() {
  tft_select_screen1(); 
  tft.fillScreen(TFT_BLACK); 
  delay(5); // 清屏后延时，稳定电平
  tft.drawChar(50, 60, '>', TFT_WHITE, TFT_BLACK, 20);
  delay(5); // 绘制后延时，确保指令生效
  digitalWrite(TFT_CS1, HIGH); 
  delay(5);
}
void tft_screen_draw_eye2_on() {
  tft_select_screen2(); 
  tft.fillScreen(TFT_BLACK); 
  tft.drawChar(60, 90, '~', TFT_WHITE, TFT_BLACK, 20);
  digitalWrite(TFT_CS2, HIGH);
  delay(5);
}
void tft_screen_draw_eye2_off() {
  tft_select_screen2(); 
  tft.fillScreen(TFT_BLACK); 
  tft.drawChar(60, 60, '<', TFT_WHITE, TFT_BLACK, 20);
  digitalWrite(TFT_CS2, HIGH);
  delay(5);
}