#include "config.h"

// ===================== 仅需修改这里的配置 =====================
// WiFi配置（填写你的WiFi名称/密码）
WiFiConfig g_wifi_config = {
  .ssid = "CaseyiPhone",  // 示例："TP-LINK_8888"
  .password = "005127666"    // 示例："12345678"
};

// 百度API配置（填写你的双应用密钥）
BaiduAPIConfig g_baidu_config = {
  .asr_api_key = "e405QZJqoWBxE47peyFr9n3G",    // 示例："123456789abcdefg"
  .asr_secret_key = "46ICavCfMXFPjD4i0a4GeNPYvfHIleDX", // 示例："abcdefg123456789"
  .emo_api_key = "DbD6ECp0qFT5tzvXFRtDxCgd",    // 示例："987654321zyxwvut"
  .emo_secret_key = "SBczAfuDOOYteDhQs9cVg0IObOFc62Jd" // 示例："zyxwvut987654321"
};

// 音频硬件配置（按你的接线修改引脚）
AudioHWConfig g_audio_config = {
  .sck_pin = 32,   // INMP441 SCK引脚
  .ws_pin = 15,    // INMP441 WS引脚
  .sd_pin = 2,    // INMP441 SD引脚
  .sample_rate = 16000,
  .duration = 2
};
// ==============================================================

// 配置初始化（校验必填项是否填写）
bool config_init() {
  // 校验WiFi配置
  if (g_wifi_config.ssid == nullptr || strlen(g_wifi_config.ssid) == 0 ||
      g_wifi_config.password == nullptr || strlen(g_wifi_config.password) == 0) {
    Serial.println("[Config] WiFi配置未填写！");
    return false;
  }

  // 校验百度API配置
  if (g_baidu_config.asr_api_key == nullptr || strlen(g_baidu_config.asr_api_key) == 0 ||
      g_baidu_config.asr_secret_key == nullptr || strlen(g_baidu_config.asr_secret_key) == 0 ||
      g_baidu_config.emo_api_key == nullptr || strlen(g_baidu_config.emo_api_key) == 0 ||
      g_baidu_config.emo_secret_key == nullptr || strlen(g_baidu_config.emo_secret_key) == 0) {
    Serial.println("[Config] 百度API配置未填写！");
    return false;
  }

  // 校验音频引脚配置
  if (g_audio_config.sck_pin == 0 || g_audio_config.ws_pin == 0 || g_audio_config.sd_pin == 0) {
    Serial.println("[Config] 音频引脚配置未填写！");
    return false;
  }

  Serial.println("[Config] 配置初始化成功");
  return true;
}