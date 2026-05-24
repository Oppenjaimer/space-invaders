#pragma once

#include "raylib.h"

#include <string_view>

/**
 * @brief Sprites atlas handling.
 */
namespace atlas {
    constexpr const char* image_path = "sprites/atlas.png";
    constexpr int sprite_count = 26;

    struct Sprite {
        const char* name;
        int pos_x, pos_y;
        int src_width, src_height;
    };

    inline constexpr Sprite sprites[sprite_count] = {
        {"alien_explode", 0, 16, 13, 8},
        {"alien_shot_explode", 22, 0, 6, 8},
        {"crab1", 28, 0, 11, 8},
        {"crab2", 39, 0, 11, 8},
        {"octopus1", 50, 0, 12, 8},
        {"octopus2", 62, 0, 12, 8},
        {"player_explode1", 74, 0, 15, 8},
        {"player_explode2", 89, 0, 16, 8},
        {"player_normal", 105, 0, 13, 8},
        {"player_shot_explode", 118, 0, 8, 8},
        {"player_shot_normal", 78, 16, 1, 4},
        {"plunger_shot1", 69, 16, 3, 6},
        {"plunger_shot2", 72, 16, 3, 6},
        {"plunger_shot3", 75, 16, 3, 6},
        {"plunger_shot4", 66, 16, 3, 6},
        {"rolling_shot2", 29, 16, 3, 7},
        {"rolling_shot4", 32, 16, 3, 7},
        {"rolling_shot13", 35, 16, 3, 7},
        {"shield", 0, 0, 22, 16},
        {"squid1", 13, 16, 8, 8},
        {"squid2", 21, 16, 8, 8},
        {"squiggly_shot1", 38, 16, 3, 7},
        {"squiggly_shot2", 41, 16, 3, 7},
        {"squiggly_shot3", 44, 16, 3, 7},
        {"squiggly_shot4", 47, 16, 3, 7},
        {"ufo", 50, 16, 16, 7},
    };

    /**
     * @brief Get sprite rectangle from atlas.
     * @param name Sprite name.
     * @return Sprite rectangle.
     */
    Rectangle get_sprite_rect(std::string_view name);
}
