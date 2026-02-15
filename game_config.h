#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <string>

class GameConfig {
public:
    static void apply(bool fps130, bool iPadView, bool magicBullet);
};

#endif // GAME_CONFIG_H