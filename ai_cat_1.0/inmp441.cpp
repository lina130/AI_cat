#include "inmp441.h"

// 全局音频实例初始化
INMP441 g_audio;

INMP441::INMP441() {
  m_buf_size = _calc_buf_size();
  m_buf = (int16_t*)malloc(m_buf_size);
  if (!m_buf) Serial.println("[Audio] 缓冲区分配失败");
}

INMP441::~INMP441() {
  if (m_buf) free(m_buf);
  if (m_init_ok) i2s_driver_uninstall(I2S_NUM_0);
}

bool INMP441::init() {
  if (!m_buf) {
    Serial.println("[Audio] 缓冲区分配失败");
    return false;
  }

  const i2s_config_t i2s_cfg = {
    // 关键修复：强制转换为i2s_mode_t类型
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = g_audio_config.sample_rate, // 引用config的采样率
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .dma_buf_count = 4,
    .dma_buf_len = 512
  };

  const i2s_pin_config_t pin_cfg = {
    .bck_io_num = g_audio_config.sck_pin, // 引用config的SCK引脚
    .ws_io_num = g_audio_config.ws_pin,   // 引用config的WS引脚
    .data_in_num = g_audio_config.sd_pin  // 引用config的SD引脚
  };

  if (i2s_driver_install(I2S_NUM_0, &i2s_cfg, 0, NULL) != ESP_OK) {
    Serial.println("[Audio] I2S驱动安装失败");
    return false;
  }
  i2s_set_pin(I2S_NUM_0, &pin_cfg);
  m_init_ok = true;
  Serial.println("[Audio] 初始化成功");
  return true;
}

bool INMP441::collect() {
  if (!m_init_ok || !m_buf) {
    Serial.println("[Audio] 未初始化");
    return false;
  }

  Serial.print("[Audio] 采集");
  Serial.print(g_audio_config.duration); // 引用config的采集时长
  Serial.println("秒音频...");

  size_t bytes_read = 0;
  if (i2s_read(I2S_NUM_0, m_buf, m_buf_size, &bytes_read, portMAX_DELAY) != ESP_OK) {
    Serial.print("[Audio] 采集失败，读取字节数：");
    Serial.println(bytes_read);
    return false;
  }

  Serial.print("[Audio] 采集完成，读取字节数：");
  Serial.println(bytes_read);
  return true;
}

int16_t* INMP441::get_buf() { return m_buf; }
size_t INMP441::get_buf_size() { return m_buf_size; }
bool INMP441::is_init() { return m_init_ok; }