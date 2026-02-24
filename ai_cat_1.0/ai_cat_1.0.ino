#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "AudioStorage.h"

// 替换成你的WiFi信息
#define WIFI_SSID "CaseyiPhone"
#define WIFI_PWD  "005127666"

WebServer server(80);

// 初始化WiFi
void initWiFi() {
  Serial.print("连接WiFi: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PWD);
  
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 20) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ WiFi连接成功！");
    Serial.print("📡 ESP32 IP地址：");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ WiFi连接失败，请检查名称/密码");
    while(1) delay(1000);
  }
}

// 处理文件上传
void handleFileUpload() {
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    Serial.print("📤 开始上传文件：");
    Serial.println(upload.filename);
    littleFS.remove("/" + upload.filename);  // 使用littleFS变量
    fs::File file = littleFS.open("/" + upload.filename, FILE_WRITE);
    if (!file) {
      Serial.println("❌ 无法创建文件");
      return;
    }
    file.close();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    fs::File file = littleFS.open("/" + upload.filename, FILE_APPEND);
    if (file) {
      file.write(upload.buf, upload.currentSize);
      file.close();
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    Serial.print("✅ 文件上传完成，大小：");
    Serial.println(upload.totalSize);
    server.send(200, "text/plain", "文件上传成功！");
    
    // 验证音频文件
    if (littleFS.exists(AUDIO_FILE_PATH)) {
      fs::File f = littleFS.open(AUDIO_FILE_PATH, "r");
      Serial.print("\n检测到音频文件：");
      Serial.print(AUDIO_FILE_PATH);
      Serial.print(" | 大小：");
      Serial.println(f.size());
      f.close();
      Serial.println("音频文件存储成功！");
    }
  }
}


void handleRoot() {
  String html = "<!DOCTYPE html>";
  html += "<html>";
  html += "<head><meta charset='UTF-8'></head>";
  html += "<body>";
  html += "<h1>ESP32 LittleFS 文件上传工具</h1>";
  html += "<form method='POST' enctype='multipart/form-data' action='/upload'>";
  html += "<input type='file' name='file' accept='.wav'><br><br>";
  html += "<input type='submit' value='上传cat.wav文件'>";
  html += "</form>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  // 1. 初始化串口（波特率115200）
  Serial.begin(115200);
  // ❌ 删掉普通ESP32不支持的while (!Serial)，避免卡壳
  // while (!Serial) delay(10);
  // ✅ 加1秒延迟，确保串口硬件完全就绪
  delay(1000);
  
  Serial.println("\n=== ESP32 音频文件上传程序启动 ===");

  // 2. 初始化LittleFS
  Serial.println("\n[初始化LittleFS...]");
  if (!audioStorageInit()) {
    Serial.println("❌ LittleFS初始化失败，程序终止");
    while(1) delay(1000);
  }

  // 3. 初始化WiFi
  Serial.println("\n[初始化WiFi...]");
  initWiFi();

  // 4. 配置Web路由
  server.on("/", handleRoot);
  server.on("/upload", HTTP_POST, []() {
    server.send(200, "text/plain", "");
  }, handleFileUpload);

  // 5. 启动Web服务器
  server.begin();
  Serial.println("✅ Web服务器已启动，访问上面的IP地址即可上传文件");
}

void loop() {
  server.handleClient();
  delay(10);
}