#include "emotion_analysis.h"

// 语音识别实现
String asr_recognize(INMP441& audio) {
  if (!is_wifi_connected() || !audio.is_init()) {
    Serial.println("[ASR] 依赖未就绪");
    return "";
  }

  String token = get_asr_token();
  if (token.isEmpty()) {
    Serial.println("[ASR] Token为空");
    return "";
  }

  String url = "https://vop.baidu.com/server_api?dev_pid=1537&cuid=esp32&token=" + token;
  HTTPClient http;
  http.begin(url);
  // 关键修复：g_audio_cfg → g_audio_config
  http.addHeader("Content-Type", "audio/pcm;rate=" + String(g_audio_config.sample_rate));
  http.addHeader("Content-Length", String(audio.get_buf_size()));

  Serial.println("[ASR] 识别中...");
  int code = http.POST((uint8_t*)audio.get_buf(), audio.get_buf_size());
  String res = "";

  if (code == HTTP_CODE_OK) {
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, http.getString());
    if (doc["err_no"].as<int>() == 0) {
      res = doc["result"][0].as<String>();
      Serial.print("[ASR] 结果：");
      Serial.println(res);
    } else {
      Serial.print("[ASR] 失败：");
      Serial.println(doc["err_msg"].as<String>());
    }
  }
  http.end();
  return res;
}

// 情绪映射
static EmoLabel _map_emo(int sentiment, float neg_prob, String text) {
  if (sentiment == 2) return EmoLabel::HAPPY;
  if (sentiment == 0) {
    if (text.indexOf("愤怒") != -1 || neg_prob > 0.8) return EmoLabel::ANGRY;
    return EmoLabel::DISAPPOINTED;
  }
  return EmoLabel::DISAPPOINTED;
}

String emo_to_str(EmoLabel label) {
  switch (label) {
    case EmoLabel::ANGRY: return "愤怒";
    case EmoLabel::HAPPY: return "开心";
    case EmoLabel::DISAPPOINTED: return "失望";
    default: return "未知";
  }
}

// 情绪分析实现
String analyze_emo(String text) {
  if (!is_wifi_connected() || text.isEmpty()) return "";

  String token = get_emo_token();
  if (token.isEmpty()) return "";

  String url = "https://aip.baidubce.com/rpc/2.0/nlp/v1/sentiment_classify?access_token=" + token;
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  DynamicJsonDocument req(512);
  req["text"] = text;
  String req_body;
  serializeJson(req, req_body);

  Serial.println("[Emo] 分析中...");
  int code = http.POST(req_body);
  String res = "";

  if (code == HTTP_CODE_OK) {
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, http.getString());
    if (doc["error_code"].as<int>() == 0) {
      int s = doc["items"][0]["sentiment"].as<int>();
      float np = doc["items"][0]["negative_prob"].as<float>();
      res = emo_to_str(_map_emo(s, np, text));
      Serial.print("[Emo] 结果：");
      Serial.println(res);
    }
  }
  http.end();
  return res;
}