#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// WiFi配置结构体
typedef struct {
  const char* ssid;    // WiFi名称
  const char* password;// WiFi密码
} WiFiConfig;

// 百度API配置结构体
typedef struct {
  const char* asr_api_key;    // 语音识别API Key
  const char* asr_secret_key; // 语音识别Secret Key
  const char* emo_api_key;    // 情绪分析API Key
  const char* emo_secret_key; // 情绪分析Secret Key
} BaiduAPIConfig;

// 音频硬件配置结构体
typedef struct {
  int sck_pin;   // INMP441 SCK引脚
  int ws_pin;    // INMP441 WS引脚
  int sd_pin;    // INMP441 SD引脚
  int sample_rate; // 采样率（默认16000）
  float duration;  // 采集时长（秒，默认0.5）
} AudioHWConfig;

// 全局配置实例声明（在config.cpp中初始化）
extern WiFiConfig g_wifi_config;
extern BaiduAPIConfig g_baidu_config;
extern AudioHWConfig g_audio_config;

// 配置初始化函数（校验配置是否填写）
bool config_init();

#endif // CONFIG_H