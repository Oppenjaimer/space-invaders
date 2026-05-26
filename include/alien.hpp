#pragma once

#include "raylib.h"

#include "config.hpp"

#include <array>

namespace alien {
    enum AlienType {
        Squid,  // Top-row
        Crab,   // Middle-row
        Octopus // Bottom-row
    };

    struct Alien {
        AlienType type;
        Rectangle sprite_rect;
        int animation_frame; // Frames: 0,1
        Vector2 pos;
        bool alive;
    };

    void set_type(Alien& alien, AlienType type);
    void advance_frame(Alien& alien);
    void init(Alien& alien);
    void update(Alien& alien);
    void draw(const Alien& alien, const Texture& atlas);
}

namespace fleet {
    struct Fleet {
        float timer;
        int direction; // Right: 1, Left: -1
    };

    void init(Fleet& fleet);
    void update(Fleet& fleet, std::array<alien::Alien, config::alien_count>& aliens);
}
