#include "atlas.hpp"
#include "config.hpp"
#include "ufo.hpp"

void ufo::init(Ufo &ufo) {
    ufo.sprite_rect = atlas::get_sprite_rect(atlas::Ufo);
    ufo.pos = {0, 0}; // Chosen randomly on spawn
    ufo.spawn_timer = 0.0f;
    ufo.direction = 0; // Chosen randomly on spawn
    ufo.alive = false;
}

void ufo::update(Ufo &ufo) {
    // Spawn
    if (!ufo.alive) ufo.spawn_timer += GetFrameTime();
    if (ufo.spawn_timer >= config::ufo_spawn_interval) {
        // Choose random direction and side to spawn
        ufo.direction = GetRandomValue(0, 1) ? -1 : 1;
        if (ufo.direction == 1) ufo.pos.x = -ufo.sprite_rect.width;
        else ufo.pos.x = config::world_width;

        ufo.pos.y = config::ufo_spacing_top;
        ufo.alive = true;
        ufo.spawn_timer -= config::ufo_spawn_interval;
    }

    // Move horizontally
    if (ufo.alive) {
        ufo.pos.x += ufo.direction * config::ufo_speed;

        // Deactivate UFO when out of world bounds
        if (ufo.pos.x <= -ufo.sprite_rect.width || ufo.pos.x >= config::world_width)
            ufo.alive = false;
    }
}

void ufo::draw(const Ufo &ufo, const Texture &atlas) {
    if (ufo.alive)
        DrawTextureRec(atlas, ufo.sprite_rect, ufo.pos, theme::red);
}
