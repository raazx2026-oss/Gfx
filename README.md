# GFX Tool Native Library

This library provides GFX settings (130 FPS, iPad view, Magic Bullet) with Shizuku integration for system-level commands. It is built for all Android ABIs via GitHub Actions.

## Building Locally

Use Android NDK and CMake:
```bash
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-21
cmake --build .