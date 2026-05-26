#pragma once

#include "raylib.h"

namespace shield {
    struct Shield {
        Rectangle sprite_rect;
        Vector2 pos;
    };

    void init(Shield& shield);
    void update(Shield& shield);
    void draw(const Shield& shield, const Texture& atlas);
}
