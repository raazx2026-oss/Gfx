#include "game_config.h"
#include <android/log.h>
#include <fstream>
#include <string>

#define LOG_TAG "GameConfig"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

void GameConfig::apply(bool fps130, bool iPadView, bool magicBullet) {
    LOGI("GameConfig::apply called");

    // Change this path to the actual game's config file
    std::string path = "/data/data/com.example.game/files/config.cfg";
    std::ofstream file(path, std::ios::app);
    if (file.is_open()) {
        file << "fps130=" << (fps130 ? "1" : "0") << std::endl;
        file << "iPadView=" << (iPadView ? "1" : "0") << std::endl;
        file << "magicBullet=" << (magicBullet ? "1" : "0") << std::endl;
        file.close();
        LOGI("Config file written");
    } else {
        LOGE("Failed to open config file (maybe no permission)");
    }
}