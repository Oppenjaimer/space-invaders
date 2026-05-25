#pragma once

#include "raylib.h"

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
        Vector2 pos;
    };

    /**
     * @brief Set an alien type and load its corresponding sprite.
     * @param alien Alien whose type to set.
     * @param type Alien type.
     */
    void set_type(Alien& alien, AlienType type);

    /**
     * @brief Initialize alien state.
     * @param alien Alien to initialize.
     */
    void init(Alien& alien);

    /**
     * @brief Handle alien movement, firing and death.
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
