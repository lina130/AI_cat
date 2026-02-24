#ifndef EMOTION_ANALYSIS_H
#define EMOTION_ANALYSIS_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "wifi_util.h"
#include "inmp441.h"

// 情绪标签枚举
enum class EmoLabel { ANGRY, HAPPY, DISAPPOINTED, UNKNOWN };

// 语音识别（封装到本文件）
String asr_recognize(INMP441& audio);

// 情绪分析
String analyze_emo(String text);

// 枚举转字符串
String emo_to_str(EmoLabel label);

#endif // EMOTION_ANALYSIS_H  // 确保闭合