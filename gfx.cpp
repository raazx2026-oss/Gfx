#include "gfx.h"
#include "shizuku.h"
#include "game_config.h"
#include <android/log.h>
#include <string>
#include <cstring>

#define LOG_TAG "GFXLib"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static std::string lastError = "";

extern "C" {

JNIEXPORT jboolean JNICALL
Java_com_example_gfxtool_NativeLib_initShizuku(JNIEnv *env, jclass clazz, jint uid) {
    bool success = Shizuku::init(uid);
    if (!success) {
        lastError = "Shizuku not available or permission denied";
        return JNI_FALSE;
    }
    lastError = "";
    return JNI_TRUE;
}

JNIEXPORT void JNICALL
Java_com_example_gfxtool_NativeLib_applySettings(JNIEnv *env, jclass clazz,
                                                 jboolean fps130, jboolean iPadView, jboolean magicBullet) {
    LOGI("applySettings called: fps130=%d, iPadView=%d, magicBullet=%d",
         fps130, iPadView, magicBullet);

    // 1. Try to use Shizuku for system-level changes
    if (Shizuku::isAvailable()) {
        // Execute commands via Shizuku
        if (fps130) {
            std::string cmd = "settings put global animator_duration_scale 0.5"; // example
            Shizuku::runCommand(cmd);
        }
        if (iPadView) {
            std::string cmd = "wm density 320"; // example: change DPI
            Shizuku::runCommand(cmd);
        }
        if (magicBullet) {
            // Some magic command
        }
    } else {
        LOGI("Shizuku not available, falling back to direct file modification");
    }

    // 2. Modify game config files directly (requires root or app's own UID)
    // We'll attempt to write to a known game directory if accessible.
    // For demonstration, we'll just log.
    GameConfig::apply(fps130, iPadView, magicBullet);

    LOGI("Settings applied successfully.");
}

JNIEXPORT jstring JNICALL
Java_com_example_gfxtool_NativeLib_getLastError(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF(lastError.c_str());
}

} // extern "C"