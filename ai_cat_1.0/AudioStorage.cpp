#include "AudioStorage.h"

// 定义全局变量，用littleFS替代fs，避免命名冲突
fs::LittleFSFS& littleFS = LittleFS;

bool audioStorageInit() {
  // 初始化ESP32原生LittleFS（自动格式化）
  if (!littleFS.begin(true)) {
    Serial.println("❌ LittleFS初始化失败（已尝试自动格式化）");
    return false; // 只有文件系统初始化失败时，才返回false
  }
  Serial.println("✅ ESP32 LittleFS初始化成功");
  
  // 验证音频文件是否存在（文件不存在不影响文件系统初始化）
  if (littleFS.exists(AUDIO_FILE_PATH)) {
    fs::File f = littleFS.open(AUDIO_FILE_PATH, "r");
    Serial.print("📄 检测到音频文件：");
    Serial.print(AUDIO_FILE_PATH);
    Serial.print(" | 大小：");
    Serial.println(f.size());
    f.close();
  } else {
    Serial.println("⚠️ 未找到音频文件：" + String(AUDIO_FILE_PATH) + "（后续可通过网页上传）");
  }
  return true; // 只要文件系统初始化成功，就返回true
}