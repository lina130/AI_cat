#include <Arduino.h>
#include <WiFi.h>
#ifndef WIFI_UTIL_H
#define WIFI_UTIL_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "config.h" // 引入配置模块

// WiFi连接（带重试+错误处理）
bool wifi_connect();

// 检查WiFi连接状态
bool is_wifi_connected();

// 获取语音识别Token（自动刷新）
String get_asr_token();

// 获取情绪分析Token（自动刷新）
String get_emo_token();

#endif // WIFI_UTIL_H
