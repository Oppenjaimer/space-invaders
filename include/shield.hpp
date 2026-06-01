#pragma once

#include "raylib.h"

#include "config.hpp"

#include <array>

namespace shield {
    struct Shield {
        Vector2 pos;
        Image image;     // CPU image for pixel modification
        Texture texture; // GPU texture for rendering
    };

    using ShieldArray = std::array<shield::Shield, config::shield_count>;

    void init(Shield& shield, const Image& atlas);
    void free(Shield& shield);
    void update(Shield& shield);
    void draw(const Shield& shield);
    Rectangle get_hitbox(const Shield& shield);
    bool apply_damage(Shield& shield, Rectangle shot_hitbox, bool shot_moving_up);
    void apply_alien_overlap(Shield& shield, Rectangle alien_hitbox);
}
