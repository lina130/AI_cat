#ifndef TFT_SCREEN_H
#define TFT_SCREEN_H

#include <Arduino.h>
#include <TFT_eSPI.h>



#define TFT_CS1  13  
#define TFT_CS2  33   

extern TFT_eSPI tft;


void tft_screen_init();       
void tft_screen_draw_eye1_off();  
void tft_screen_draw_eye2_off();  
void tft_screen_draw_eye1_on();  
void tft_screen_draw_eye2_on();  
void tft_select_screen1();  
void tft_select_screen2();   

#endif 