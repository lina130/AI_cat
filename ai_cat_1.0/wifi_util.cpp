#include "wifi_util.h"

// 私有变量（仅本文件可见）
static String s_asr_token = "";
static String s_emo_token = "";
static unsigned long s_asr_expire = 0;
static unsigned long s_emo_expire = 0;
const unsigned long TOKEN_VALID = 2592000000; // Token有效期30天

// 私有函数：通用Token获取
static bool _get_token(String& token, unsigned long& expire, const char* api_key, const char* secret_key) {
  if (millis() < expire) return true;

  HTTPClient http;
  String url = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=" +
               String(api_key) + "&client_secret=" + String(secret_key);
  
  http.begin(url);
  int code = http.GET();
  if (code != HTTP_CODE_OK) {
    Serial.print("[WiFi] Token获取失败，错误码：");
    Serial.println(code);
    http.end();
    return false;
  }

  DynamicJsonDocument doc(512);
  deserializeJson(doc, http.getString());
  token = doc["access_token"].as<String>();
  expire = millis() + TOKEN_VALID;
  http.end();
  return true;
}

// WiFi连接实现（使用config模块的WiFi配置）
bool wifi_connect() {
  if (WiFi.status() == WL_CONNECTED) return true;

  Serial.print("[WiFi] 连接中：");
  Serial.println(g_wifi_config.ssid); // 引用config的WiFi名称
  WiFi.disconnect(true);
  WiFi.begin(g_wifi_config.ssid, g_wifi_config.password); // 引用config的WiFi密码

  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 20) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("\n[WiFi] 连接成功，IP：");
    Serial.println(WiFi.localIP().toString());
    return true;
  } else {
    Serial.println("\n[WiFi] 连接失败");
    return false;
  }
}

bool is_wifi_connected() {
  return WiFi.status() == WL_CONNECTED;
}

// 获取语音识别Token（使用config的ASR密钥）
String get_asr_token() {
  if (_get_token(s_asr_token, s_asr_expire, g_baidu_config.asr_api_key, g_baidu_config.asr_secret_key)) {
    return s_asr_token;
  }
  return "";
}

// 获取情绪分析Token（使用config的EMO密钥）
String get_emo_token() {
  if (_get_token(s_emo_token, s_emo_expire, g_baidu_config.emo_api_key, g_baidu_config.emo_secret_key)) {
    return s_emo_token;
  }
  return "";
}