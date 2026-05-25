#include "alien.hpp"
#include "atlas.hpp"
#include "config.hpp"

void alien::set_type(Alien &alien, AlienType type) {
    alien.type = type;

    switch (type) {
        case Squid:   alien.sprite_rect = atlas::get_sprite_rect(atlas::Squid1);   break;
        case Crab:    alien.sprite_rect = atlas::get_sprite_rect(atlas::Crab1);    break;
        case Octopus: alien.sprite_rect = atlas::get_sprite_rect(atlas::Octopus1); break;
    }
}

void alien::init(Alien &alien) {
    alien.pos = {0, 0}; // Computed when creating all aliens
}

void alien::update(Alien &alien) {
    // TODO: move aliens and make them shoot
    (void)alien;
}

void alien::draw(Texture atlas, const Alien &alien) {
    Color color;
    switch (alien.type) {
        case Squid:   color = theme::purple; break;
        case Crab:    color = theme::blue;   break;
        case Octopus: color = theme::aqua;   break;
    }

    DrawTextureRec(atlas, alien.sprite_rect, alien.pos, color);
}
