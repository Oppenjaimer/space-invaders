#pragma once

#include "raylib.h"

namespace config {
    // Application
    constexpr int fps = 60;
    constexpr const char* title = "Space Invaders";

    // World
    constexpr int world_width = 224;
    constexpr int world_height = 256;

    // Screen
    constexpr int initial_scale = 3;
    constexpr int screen_width = world_width * initial_scale;
    constexpr int screen_height = world_height * initial_scale;

    // Resources
    constexpr const char* resource_dir = "resources";
    constexpr const char* icon_file = "icon.png";
    constexpr const char* atlas_file = "sprites/atlas.png";

    // Player
    constexpr int player_spacing_sides = 2;
    constexpr int player_spacing_bottom = 32;
    constexpr int player_speed = 1;
    constexpr int player_shot_speed = 3;

    // Shields
    constexpr int shield_spacing_bottom = 48;
    constexpr int shield_spacing_left = 32;
    constexpr int shield_spacing_right = 35;
    constexpr int shield_spacing_inner = 23;
    constexpr int shield_count = 4;

    // Aliens
    constexpr int alien_rows = 5;
    constexpr int alien_cols = 11;
    constexpr int alien_count = alien_rows * alien_cols;
    constexpr int alien_spacing_top = 64;
    constexpr int alien_spacing_sides = 26;
    constexpr int alien_spacing_inner_x = 4;
    constexpr int alien_spacing_inner_y = 8;
    constexpr int alien_spacing_jump = 2;
    constexpr int alien_jump_x = 2;
    constexpr int alien_jump_y = 8;
    constexpr float alien_move_interval = 1.0f / fps;
    constexpr float alien_grace_period = 2.0f;
    constexpr int alien_shot_limit = 3;
    constexpr float alien_shot_speed = 2;
    constexpr float alien_shot_interval = 1.0f;
    constexpr float alien_shot_animation_rate = 0.1f;

    // UFO
    constexpr int ufo_spacing_top = 32;
    constexpr float ufo_speed = 0.85;
    constexpr float ufo_spawn_interval = 25.6f;
}

/**
 * Gruvbox Dark color palette.
 */
namespace theme {
    // Background
    inline const Color bg0_hard = {29, 32, 33, 255};
    inline const Color bg0 = {40, 40, 40, 255};
    inline const Color bg1 = {60, 56, 54, 255};
    inline const Color bg2 = {80, 73, 69, 255};
    inline const Color bg3 = {102, 92, 84, 255};
    inline const Color bg4 = {124, 111, 100, 255};

    // Foreground
    inline const Color fg4 = {168, 153, 132, 255};
    inline const Color fg3 = {189, 174, 147, 255};
    inline const Color fg2 = {213, 196, 161, 255};
    inline const Color fg1 = {235, 219, 178, 255};
    inline const Color fg0 = {251, 241, 199, 255};

    // Normal colors
    inline const Color red = {204, 36, 29, 255};
    inline const Color green = {152, 151, 26, 255};
    inline const Color yellow = {215, 153, 33, 255};
    inline const Color blue = {69, 133, 136, 255};
    inline const Color purple = {177, 98, 134, 255};
    inline const Color aqua = {104, 157, 106, 255};
    inline const Color orange = {214, 93, 14, 255};
    inline const Color gray = {146, 131, 116, 255};

    // Bright colors
    inline const Color bright_red = {251, 73, 52, 255};
    inline const Color bright_green = {184, 187, 38, 255};
    inline const Color bright_yellow = {250, 189, 47, 255};
    inline const Color bright_blue = {131, 165, 152, 255};
    inline const Color bright_purple = {211, 134, 155, 255};
    inline const Color bright_aqua = {142, 192, 124, 255};
    inline const Color bright_orange = {254, 128, 25, 255};
    inline const Color bright_gray = {168, 153, 132, 255};
}
