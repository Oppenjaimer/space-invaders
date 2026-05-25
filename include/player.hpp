#pragma once

#include "raylib.h"

/**
 * @brief Player cannon management.
 */
namespace player {
    struct Player {
        // Cannon
        Rectangle sprite_rect;
        Vector2 pos;

        // Shot
        bool shot_active;
        Rectangle shot_rect;
        Vector2 shot_pos;
    };

    /**
     * @brief Initialize player state.
     * @param player Player to initialize.
     */
    void init(Player& player);

    /**
     * @brief Handle player movement, firing and death.
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
