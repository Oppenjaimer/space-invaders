#pragma once

#include "raylib.h"

namespace player {
    struct Player {
        // Cannon
        Rectangle sprite_rect;
        Vector2 pos;

        // Shot
        bool shot_active;
        Rectangle shot_rect;
        Vector2 shot_pos;
    };

    void init(Player& player);
    void update(Player& player);
    void draw(const Player& player, const Texture& atlas);
}
