#ifndef AUDIOSTORAGE_H
#define AUDIOSTORAGE_H

#include <Arduino.h>
#include <LittleFS.h>  // ESP32原生LittleFS

// 音频文件路径（根目录，对应data/cat.wav）
#define AUDIO_FILE_PATH "/cat.wav"

// 重命名变量为littleFS，避免和fs命名空间冲突
extern fs::LittleFSFS& littleFS;

// 初始化LittleFS
bool audioStorageInit();

#endif