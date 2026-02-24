# 🐱 AI Cat - Multi-Modal Interactive Bionic Cat (ESP32)

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-ESP32-lightgrey.svg)
![Framework](https://img.shields.io/badge/framework-Arduino-00979D.svg)

## 📝 Introduction
This project is a multi-modal intelligent bionic robot (AI Cat) based on the ESP32 microcontroller. The system integrates hardware-level I2S audio recording and playback, Baidu Cloud ASR (Automatic Speech Recognition) & NLP (Natural Language Processing) for emotion analysis, dual TFT screens for dynamic facial expressions, and multi-DOF (Degree of Freedom) servos for physical action feedback. 

Additionally, the project features a built-in local WebServer for LittleFS file management, allowing users to upload `.wav` audio files wirelessly via a web browser.

## ✨ Key Features
* **🗣️ Smart Voice Interaction**: Utilizes the INMP441 microphone (I2S) for high-quality environmental audio capture, seamlessly integrated with Baidu Cloud ASR via HTTP.
* **🧠 Cloud Emotion Engine**: Calls the Baidu NLP API to analyze the sentiment of user inputs in real-time (Happy, Angry, Disappointed) and calculates the Negative Probability.
* **👀 Multi-Modal Physical Feedback**:
  * **Visual**: Drives dual TFT screens via SPI, synchronizing with the emotion engine to display dynamic ASCII expressions (`~`, `>`, `<`).
  * **Action**: Concurrently controls 4 servos (head, ears, tail) via PWM to perform physical movements matching the current emotional state.
* **🌐 Wireless File Management**: Establishes a local WebServer on the ESP32, enabling users to upload audio files directly to the LittleFS flash memory for persistent storage without physical wired connections.
* **⚙️ Highly Modular Architecture**: The hardware abstraction layer (BSP), network communication layer, and business logic layer are strictly decoupled. All configuration parameters are centralized in `config.cpp` for excellent maintainability.

## 🛠️ Hardware & Pin Mapping
> **Note**: Please connect your hardware according to the definitions in `config.cpp` and individual module headers.

| Module Type | Hardware Model | ESP32 Pin Definition | Description |
| :--- | :--- | :--- | :--- |
| **Microphone** | INMP441 | SCK=32, WS=15, SD=2 | I2S RX (Audio Capture) |
| **Audio DAC** | I2S DAC Module | BCLK=26, LRC=25, DOUT=22 | I2S TX (Audio Playback) |
| **Servos** | SG90 x4 | 14 (Body), 16 (Left Ear), 4 (Right Ear) | PWM Drive |
| **Touch Sensor** | TTP223 | Defined in `TouchModule.h` | Capacitive Touch Input |
| **Displays** | Dual TFT Screens | CS1, CS2, DC (See `tft_screen`) | SPI Communication |


## 🚀 Getting Started

### 1. Library Dependencies
Before compiling, ensure the following libraries are installed in your Arduino IDE:
* `TFT_eSPI` (For screen driving)
* `ArduinoJson` (For parsing Baidu API JSON responses)
* ESP32 built-in libraries: `WiFi.h`, `WebServer.h`, `LittleFS.h`, `HTTPClient.h`

### 2. Configuration
Open `config.cpp` and modify the following credentials:
1. **WiFi Settings**: Enter your local network's `SSID` and `Password`.
2. **API Keys**: Apply for Speech Recognition and NLP API keys at the [Baidu AI Cloud Console](https://console.bce.baidu.com/), and fill in your `API_KEY` and `SECRET_KEY`.

### 3. Build & Flash
* **Board Selection**: Select `ESP32 Dev Module` (or your specific board model).
* **Partition Scheme**: In the Arduino IDE, go to `Tools -> Partition Scheme` and select **Default 4MB with spiffs (1.2MB APP/1.5MB SPIFFS)** or a larger storage option. Otherwise, the LittleFS initialization will fail.

### 4. How to Upload Audio Files
1. Flash the compiled code to your ESP32.
2. Open the Serial Monitor (Baud rate: `115200`) and wait for the device to connect to WiFi.
3. Note the IP address printed in the console (e.g., `192.168.1.xxx`).
4. Open a web browser on your PC/Smartphone and enter the IP address to access the Web Upload Portal.
5. Select your `.wav` file and click upload. The file will be automatically saved to the ESP32's LittleFS.

## 📄 License
This project is licensed under the [MIT License](LICENSE). Copyright (c) 2026 Linyuhao.
