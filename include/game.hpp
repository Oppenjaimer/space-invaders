#pragma once

#include "raylib.h"

#include "alien.hpp"
#include "player.hpp"
#include "shield.hpp"

#include <array>

/**
 * @brief Global game state management.
 */
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

    /**
     * @brief Initialize game state.
     * @param state State to initialize.
     */
    void init(State& state);

    /**
     * @brief Free allocated game state memory.
     * @param state State to free.
     */
    void free(State& state);

    /**
     * @brief Update game logic.
     * @param state Current game state.
     */
    void update(State& state);

    /**
     * @brief Draw to virtual world.
     * @param state Current game state.
     */
    void draw_world(const State& state);

    /**
     * @brief Draw to window screen.
     * @param state Current game state.
     */
    void draw_screen(const State& state);
}
