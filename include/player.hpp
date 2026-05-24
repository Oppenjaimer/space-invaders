#pragma once

#include "raylib.h"

/**
 * @brief Player cannon management.
 */
namespace player {
    struct Player {
        Rectangle sprite_rect;
        Vector2 pos;
    };

    /**
     * @brief Initialize player state.
     * @param player Player to initialize.
     */
    void init(Player& player);

    /**
     * @brief Handle player movement and firing.
     * @param player Player to update.
     */
    void update(Player& player);

    /**
     * @brief Draw player to screen.
     * @param atlas Atlas to fetch sprite from.
     * @param player Player to draw.
     */
    void draw(Texture atlas, const Player& player);
}
