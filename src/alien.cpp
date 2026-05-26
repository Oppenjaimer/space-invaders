#include "alien.hpp"
#include "atlas.hpp"

/**
 * @brief Set alien sprite rectangle.
 * @param alien Alien whose sprite rectangle to set.
 */
static void set_sprite_rect(alien::Alien& alien) {
    if (alien.animation_frame == 0) {
        switch (alien.type) {
            case alien::Squid:   alien.sprite_rect = atlas::get_sprite_rect(atlas::Squid1);   break;
            case alien::Crab:    alien.sprite_rect = atlas::get_sprite_rect(atlas::Crab1);    break;
            case alien::Octopus: alien.sprite_rect = atlas::get_sprite_rect(atlas::Octopus1); break;
        }
    } else {
        switch (alien.type) {
            case alien::Squid:   alien.sprite_rect = atlas::get_sprite_rect(atlas::Squid2);   break;
            case alien::Crab:    alien.sprite_rect = atlas::get_sprite_rect(atlas::Crab2);    break;
            case alien::Octopus: alien.sprite_rect = atlas::get_sprite_rect(atlas::Octopus2); break;
        }
    }
}

void alien::set_type(Alien &alien, AlienType type) {
    alien.type = type;
    set_sprite_rect(alien);
}

void alien::advance_frame(Alien &alien) {
    alien.animation_frame = (alien.animation_frame == 0) ? 1 : 0;
    set_sprite_rect(alien);
}

void alien::init(Alien &alien) {
    alien.animation_frame = 0;
    alien.pos = {0, 0}; // Computed when creating all aliens
    alien.alive = true;
}

void alien::update(Alien &alien) {
    // TODO: make aliens shoot
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

void fleet::init(Fleet& fleet) {
    fleet.timer = 0.0f;
    fleet.direction = 1;
}

void fleet::update(std::array<alien::Alien, config::alien_count>& aliens, Fleet& fleet) {
    // Count alive aliens
    int alive = 0;
    for (const alien::Alien& alien : aliens) {
        if (alien.alive) alive++;
    }

    float interval = (float)alive * config::alien_interval;

    fleet.timer += GetFrameTime();
    if (fleet.timer >= interval) {
        // Check if any alive alien has hit the edge
        bool hit_edge = false;
        for (const alien::Alien& alien : aliens) {
            if (!alien.alive) continue;

            // Only check right edge when moving right, likewise for left
            bool hit_right = (fleet.direction == 1) && (alien.pos.x + alien.sprite_rect.width >= config::world_width - config::alien_spacing_jump);
            bool hit_left = (fleet.direction == -1) && (alien.pos.x <= config::alien_spacing_jump);

            if (hit_right || hit_left) {
                hit_edge = true;
                break;
            }
        }

        // Move alive aliens
        for (alien::Alien& alien : aliens) {
            if (!alien.alive) continue;

            if (hit_edge) alien.pos.y += config::alien_jump_y;
            else alien.pos.x += fleet.direction * config::alien_jump_x;

            alien::advance_frame(alien);
        }

        // Reverse direction if edge hit
        if (hit_edge) fleet.direction *= -1;

        fleet.timer -= interval;
    }
}
