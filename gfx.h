#ifndef GFX_H
#define GFX_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jboolean JNICALL
Java_com_example_gfxtool_NativeLib_initShizuku(JNIEnv *env, jclass clazz, jint uid);

JNIEXPORT void JNICALL
Java_com_example_gfxtool_NativeLib_applySettings(JNIEnv *env, jclass clazz,
                                                 jboolean fps130, jboolean iPadView, jboolean magicBullet);

JNIEXPORT jstring JNICALL
Java_com_example_gfxtool_NativeLib_getLastError(JNIEnv *env, jclass clazz);

#ifdef __cplusplus
}
#endif

#endif // GFX_H