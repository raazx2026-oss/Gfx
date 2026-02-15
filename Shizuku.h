#ifndef SHIZUKU_H
#define SHIZUKU_H

#include <string>

class Shizuku {
public:
    static bool init(int uid);
    static bool isAvailable();
    static bool runCommand(const std::string& command);
};

#endif // SHIZUKU_H