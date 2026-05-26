#pragma once

#include "raylib.h"

#include "config.hpp"

#include <array>

namespace shield {
    struct Shield {
        Rectangle sprite_rect;
        Vector2 pos;
    };

    using ShieldArray = std::array<shield::Shield, config::shield_count>;

    void init(Shield& shield);
    void update(Shield& shield);
    void draw(const Shield& shield, const Texture& atlas);
}
