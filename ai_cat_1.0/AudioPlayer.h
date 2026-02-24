#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <Arduino.h>
#include <driver/i2s.h>

// IO17接PAM8403 INL
#define I2S_BCLK_PIN 26
#define I2S_LRC_PIN 25
#define I2S_DIN_PIN 17

bool audioPlayerInit();
void playAudioFromFlash(); // 播放Flash里的音频

#endif