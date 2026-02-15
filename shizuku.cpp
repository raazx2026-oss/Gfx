#include "shizuku.h"
#include <android/log.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <string>

#define LOG_TAG "Shizuku"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// Shizuku uses a Unix domain socket at /dev/socket/shizuku
static const char* SHIZUKU_SOCKET = "/dev/socket/shizuku";
static bool shizukuAvailable = false;

static int connectSocket() {
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
        LOGE("Failed to create socket");
        return -1;
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SHIZUKU_SOCKET, sizeof(addr.sun_path) - 1);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        LOGE("Failed to connect to Shizuku socket");
        close(sock);
        return -1;
    }
    return sock;
}

bool Shizuku::init(int uid) {
    // Check if Shizuku is available by attempting to connect
    int sock = connectSocket();
    if (sock < 0) {
        shizukuAvailable = false;
        return false;
    }
    // Send a handshake or auth request (simplified)
    // In real Shizuku API, you'd need to send the uid and verify.
    // For demo, we just close.
    close(sock);
    shizukuAvailable = true;
    return true;
}

bool Shizuku::isAvailable() {
    return shizukuAvailable;
}

bool Shizuku::runCommand(const std::string& command) {
    if (!shizukuAvailable) return false;

    int sock = connectSocket();
    if (sock < 0) return false;

    // Construct a simple protocol: send command length then command
    uint32_t len = command.size();
    if (write(sock, &len, sizeof(len)) != sizeof(len)) {
        LOGE("Failed to send command length");
        close(sock);
        return false;
    }
    if (write(sock, command.c_str(), len) != (ssize_t)len) {
        LOGE("Failed to send command");
        close(sock);
        return false;
    }

    // Wait for response (optional)
    char result;
    if (read(sock, &result, 1) != 1) {
        LOGE("Failed to read response");
    }

    close(sock);
    return true;
}