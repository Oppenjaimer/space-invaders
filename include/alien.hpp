#pragma once

#include "raylib.h"

#include "config.hpp"

#include <array>

/**
 * @brief Alien invaders management.
 */
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

    /**
     * @brief Set alien type and load its corresponding sprite.
     * @param alien Alien whose type to set.
     * @param type Alien type.
     */
    void set_type(Alien& alien, AlienType type);

    /**
     * @brief Advance alien animation frame.
     * @param alien Alien whose frame to advance.
     */
    void advance_frame(Alien& alien);

    /**
     * @brief Initialize alien state.
     * @param alien Alien to initialize.
     */
    void init(Alien& alien);

    /**
     * @brief Handle alien firing and death.
     * @param alien Alien to update.
     */
    void update(Alien& alien);

    /**
     * @brief Draw alien to screen.
     * @param atlas Atlas to fetch sprite from.
     * @param alien Alien to draw.
     */
    void draw(Texture atlas, const Alien& alien);
}

/**
 * @brief Alien fleet timed movement management.
 */
namespace fleet {
    struct Fleet {
        float timer;
        int direction; // 1 right, -1 left
    };

    /**
     * @brief Initialize fleet state.
     * @param fleet Fleet to initialize.
     */
    void init(Fleet& fleet);

    /**
     * @brief Handle fleet movement and animation.
     * @param aliens Array of aliens.
     * @param fleet Fleet to update.
     */
    void update(std::array<alien::Alien, config::alien_count>& aliens, Fleet& fleet);
}
