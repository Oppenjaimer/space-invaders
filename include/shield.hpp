#pragma once

#include "raylib.h"

/**
 * @brief Shields handling.
 */
namespace shield {
    struct Shield {
        Rectangle sprite_rect;
        Vector2 pos;
    };

    /**
     * @brief Initialize shield state.
     * @param shield Shield to initialize.
     */
    void init(Shield& shield);

    /**
     * @brief Handle shield damage.
     * @param shield Shield to update.
     */
    void update(Shield& shield);

    /**
     * @brief Draw shield to screen.
     * @param atlas Atlas to fetch sprite from.
     * @param shield Shield to draw.
     */
    void draw(Texture atlas, const Shield& shield);
}
