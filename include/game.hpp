#pragma once

#include "raylib.h"

#include "alien.hpp"
#include "player.hpp"
#include "shield.hpp"

#include <array>

namespace game {
    struct State {
        // Textures
        RenderTexture target;
        Texture atlas;

        // Components
        player::Player player;
        std::array<shield::Shield, config::shield_count> shields;
        std::array<alien::Alien, config::alien_count> aliens;
        fleet::Fleet fleet;
    };

    void init(State& state);
    void free(State& state);
    void update(State& state);
    void draw_world(const State& state);
    void draw_screen(const State& state);
}
