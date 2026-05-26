#include "atlas.hpp"
#include "config.hpp"
#include "shield.hpp"

void shield::init(Shield &shield) {
    shield.sprite_rect = atlas::get_sprite_rect(atlas::Shield);
    shield.pos = {0, 0}; // Computed when creating all shields
}

void shield::update(Shield &shield) {
    // TODO: modify texture when damaged
    (void)shield;
}

void shield::draw(const Shield &shield, const Texture& atlas) {
    DrawTextureRec(atlas, shield.sprite_rect, shield.pos, theme::yellow);
}
