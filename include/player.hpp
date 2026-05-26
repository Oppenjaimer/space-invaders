#pragma once

#include "raylib.h"

namespace player_shot {
    struct PlayerShot {
        bool active;
        Rectangle sprite_rect;
        Vector2 pos;
    };

    void init(PlayerShot& shot);
    void update(PlayerShot& shot);
    void draw(const PlayerShot& shot, const Texture& atlas);
    void fire(PlayerShot& shot, int x, int y);
}

namespace player {
    struct Player {
        Rectangle sprite_rect;
        Vector2 pos;
        player_shot::PlayerShot shot;
    };

    void init(Player& player);
    void update(Player& player);
    void draw(const Player& player, const Texture& atlas);
}
