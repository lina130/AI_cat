#ifndef INMP441_H
#define INMP441_H

#include <Arduino.h>
#include <driver/i2s.h>
#include "config.h" // 引入配置模块

class INMP441 {
private:
  int16_t* m_buf = nullptr;
  size_t m_buf_size = 0;
  bool m_init_ok = false;

  // 计算缓冲区大小（使用config的音频配置）
  size_t _calc_buf_size() {
    return g_audio_config.sample_rate * g_audio_config.duration * sizeof(int16_t);
  }

public:
  INMP441();
  ~INMP441();

  // 初始化I2S与缓冲区
  bool init();

  // 采集音频
  bool collect();

  // 获取缓冲区指针
  int16_t* get_buf();

  // 获取缓冲区大小（字节）
  size_t get_buf_size();

  // 检查初始化状态
  bool is_init();
};

// 全局音频实例
extern INMP441 g_audio;

#endif // INMP441_H