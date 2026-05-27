#pragma once

#include "raylib.h"

#include "alien.hpp"
#include "player.hpp"
#include "shield.hpp"
#include "ufo.hpp"

namespace game {
    struct State {
        // Textures
        RenderTexture target;
        Texture atlas;

        // Components
        player::Player player;
        shield::ShieldArray shields;
        alien::AlienArray aliens;
        alien_shot::AlienShotArray alien_shots;
        fleet::Fleet fleet;
        ufo::Ufo ufo;
    };

    void init(State& state);
    void free(State& state);
    void update(State& state);
    void draw_world(const State& state);
    void draw_screen(const State& state);
}
