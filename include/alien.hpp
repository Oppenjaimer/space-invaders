#pragma once

#include "raylib.h"

#include "config.hpp"

#include <array>

namespace alien_shot {
    enum ShotType {
        Plunger,
        Rolling,
        Squiggly
    };

    struct AlienShot {
        ShotType type;
        bool active;
        Rectangle sprite_rect;
        int animation_frame; // Frames: 0,1,2,3
        float animation_timer;
        Vector2 pos;
        bool exploding;
        float explosion_timer;
    };

    using AlienShotArray = std::array<alien_shot::AlienShot, config::alien_shot_limit>;

    void advance_frame(AlienShot& shot);
    void init(AlienShot& shot);
    void update(AlienShot& shot);
    void draw(const AlienShot& shot, const Texture& atlas);
    void fire(AlienShot& shot, ShotType type, int x, int y);
    void explode(AlienShot& shot);
    Rectangle get_hitbox(const AlienShot& shot);
}

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
        bool exploding;
        float explosion_timer;
    };

    using AlienArray = std::array<alien::Alien, config::alien_count>;

    void set_type(Alien& alien, AlienType type);
    void advance_frame(Alien& alien);
    void init(Alien& alien);
    void update(Alien& alien);
    void draw(const Alien& alien, const Texture& atlas);
    void explode(Alien& alien);
    Rectangle get_hitbox(const Alien& alien);
}

namespace fleet {
    struct Fleet {
        float shot_timer;
        float move_timer;
        int direction; // Right: 1, Left: -1
    };

    void init(Fleet& fleet);
    void update(Fleet& fleet, alien::AlienArray& aliens, alien_shot::AlienShotArray& shots, float player_x_min, float player_x_max);
}
