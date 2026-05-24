#include "atlas.hpp"

Rectangle atlas::get_sprite_rect(std::string_view name) {
    for (const Sprite& sprite : sprites) {
        if (sprite.name == name)
            return {
                (float)sprite.pos_x, (float)sprite.pos_y,
                (float)sprite.src_width, (float)sprite.src_height
            };
    }

    return {0, 0, 0, 0};
}
