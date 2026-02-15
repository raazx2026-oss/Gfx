#include "game_config.h"
#include <android/log.h>
#include <fstream>
#include <string>
#include <cstdlib>

#define LOG_TAG "GameConfig"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// This is a stub – in a real tool you'd locate the game's config directory.
// For demonstration, we'll just log.
void GameConfig::apply(bool fps130, bool iPadView, bool magicBullet) {
    LOGI("GameConfig::apply called");

    // Example: Write to a file in /data/data/com.example.game/files/config.cfg
    // But we need root or to be the same UID. We'll just simulate.
    std::string path = "/data/data/com.example.game/files/config.cfg";
    std::ofstream file(path, std::ios::app);
    if (file.is_open()) {
        file << "fps130=" << (fps130 ? "1" : "0") << std::endl;
        file << "iPadView=" << (iPadView ? "1" : "0") << std::endl;
        file << "magicBullet=" << (magicBullet ? "1" : "0") << std::endl;
        file.close();
        LOGI("Config file written");
    } else {
        LOGE("Failed to open config file");
    }
}