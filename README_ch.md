# 🐱 AI Cat - 基于 ESP32 的多模态交互智能仿生猫

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-ESP32-lightgrey.svg)
![Framework](https://img.shields.io/badge/framework-Arduino-00979D.svg)

## 📝 项目简介
本项目是一个基于 ESP32 开发的多模态智能仿生机器人（AI Cat）。系统集成了 I2S 硬件级音频录放、百度云 ASR（语音识别）与 NLP（情感分析）、双 TFT 屏幕表情交互、以及多自由度舵机动作反馈。
此外，项目内置了基于 WebServer 的局域网文件系统（LittleFS）管理工具，支持通过浏览器无线 OTA 上传音频素材。

## ✨ 核心特性 (Key Features)
* **🗣️ 智能语音交互**：基于 INMP441（I2S）进行高质量环境拾音，通过 HTTP 协议对接百度云 ASR 实现语音转文字。
* **🧠 云端情绪引擎**：调用百度自然语言处理（NLP）API，实时分析用户输入语句的情感倾向（开心、愤怒、失望），并计算 Negative Probability。
* **👀 多模态物理反馈**：
  * **视觉**：通过 SPI 驱动双 TFT 屏幕，配合情绪引擎实时切换动态颜文字表情（`~`, `>`, `<` 等）。
  * **动作**：通过 PWM 并发控制 4 个舵机（头部、耳朵、尾巴），实现与情绪匹配的肢体动作。
* **🌐 无线文件管理**：通过 ESP32 建立 WebServer，用户可直接在电脑/手机浏览器中将 `.wav` 音频文件上传至单片机的 LittleFS 闪存中进行持久化存储。
* **⚙️ 高度模块化架构**：硬件驱动层（BSP）、网络通信层与业务逻辑层完全解耦，配置参数集中于 `config.cpp`，具备极强的代码可维护性。

## 🛠️ 硬件引脚映射 (Pin Mapping)
> **注意**：使用前请根据 `config.cpp` 和各模块的定义连接硬件。

| 模块类别 | 硬件型号 | 引脚定义 (ESP32) | 备注 |
| :--- | :--- | :--- | :--- |
| **麦克风** | INMP441 | SCK=32, WS=15, SD=2 | I2S RX (采集) |
| **音频功放** | I2S DAC | BCLK=26, LRC=25, DOUT=22 | I2S TX (播放) |
| **舵机控制** | SG90 x4 | 14(身体), 16(左耳), 4(右耳) | PWM 驱动 |
| **触摸感知** | TTP223 | 在 `TouchModule.h` 中定义 | 电容触摸输入 |
| **显示模块** | 双 TFT 屏 | CS1, CS2, DC 见 `tft_screen` | SPI 通信 |


## 🚀 快速开始 (Getting Started)

### 1. 依赖库安装
在编译此项目前，请确保在 Arduino IDE 中安装了以下第三方库：
* `TFT_eSPI` (屏幕驱动)
* `ArduinoJson` (解析百度 API 的 JSON 响应)
* ESP32 官方内核自带库：`WiFi.h`, `WebServer.h`, `LittleFS.h`, `HTTPClient.h`

### 2. 配置参数
打开 `config.cpp`，修改以下信息：
1. **WiFi 设置**：填入你的局域网 SSID 和 Password。
2. **API 密钥**：前往[百度智能云控制台](https://console.bce.baidu.com/)申请语音识别和 NLP 接口，填入你的 `API_KEY` 和 `SECRET_KEY`。

### 3. 编译与烧录
* 开发板选择：`ESP32 Dev Module`（或你对应的具体型号）。
* 分区表设置：请务必在 Arduino IDE 的 `Tools -> Partition Scheme` 中选择 **Default 4MB with spiffs (1.2MB APP/1.5MB SPIFFS)** 或更大存储的分区，否则 LittleFS 初始化会失败。

### 4. 音频文件上传使用方法
1. 将代码烧录进 ESP32。
2. 打开串口监视器（波特率 `115200`），等待设备连接 WiFi。
3. 记录串口打印出的 IP 地址（如 `192.168.1.xxx`）。
4. 在电脑浏览器输入该 IP 地址，进入 Web 上传页面。
5. 选择准备好的 `.wav` 音频文件并点击上传，文件将自动保存至 ESP32 的 LittleFS 中。

## 📄 开源协议
本项目基于 [MIT License](LICENSE) 协议开源。