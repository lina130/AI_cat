#include "AudioStorage.h"
#include "driver/i2s.h"

// I2S硬件引脚（根据你的硬件调整）
#define I2S_BCLK 26
#define I2S_LRC 25
#define I2S_DOUT 22

bool audioPlayerInit() {
  i2s_config_t i2s_config = {
    // 显式转换为i2s_mode_t，解决类型转换错误
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = 512,
    .use_apll = false
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num = I2S_LRC,
    .data_out_num = I2S_DOUT,
    .data_in_num = I2S_PIN_NO_CHANGE
  };

  // 安装I2S驱动
  if (i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL) != ESP_OK) {
    Serial.println("❌ I2S驱动安装失败");
    return false;
  }
  // 设置I2S引脚
  if (i2s_set_pin(I2S_NUM_0, &pin_config) != ESP_OK) {
    Serial.println("❌ I2S引脚配置失败");
    return false;
  }
  Serial.println("✅ 音频播放器初始化成功");
  return true;
}

void playAudioFromFlash() {
  // 使用修复后的littleFS变量，避免命名冲突
  fs::File audioFile = littleFS.open(AUDIO_FILE_PATH, "r");
  if (!audioFile) {
    Serial.println("❌ 打开音频文件失败");
    return;
  }

  Serial.println("▶️ 开始播放音频...");
  audioFile.seek(44);  // 跳过WAV文件头
  
  uint8_t buffer[1024];
  size_t bytesRead;
  while (audioFile.available()) {
    bytesRead = audioFile.read(buffer, sizeof(buffer));
    size_t bytesWritten;
    i2s_write(I2S_NUM_0, buffer, bytesRead, &bytesWritten, portMAX_DELAY);
  }
  
  audioFile.close();
  i2s_zero_dma_buffer(I2S_NUM_0);
  Serial.println("🔚 音频播放完成");
}