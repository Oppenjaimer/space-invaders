#pragma once

#include "raylib.h"

namespace ufo {
    struct Ufo {
        Rectangle sprite_rect;
        Vector2 pos;
        float spawn_timer;
        int direction; // Right: 1, Left: -1
        bool alive;
    };

    void init(Ufo& ufo);
    void update(Ufo& ufo);
    void draw(const Ufo& ufo, const Texture& atlas);
    Rectangle get_hitbox(const Ufo& ufo);
}
