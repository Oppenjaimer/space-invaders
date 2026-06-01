#pragma once

#include "raylib.h"

namespace player_shot {
    struct PlayerShot {
        bool active;
        Rectangle sprite_rect;
        Vector2 pos;
        bool exploding;
        float explosion_timer;
    };

    void init(PlayerShot& shot);
    void update(PlayerShot& shot);
    void draw(const PlayerShot& shot, const Texture& atlas);
    void fire(PlayerShot& shot, int x, int y);
    void explode(PlayerShot& shot);
    Rectangle get_hitbox(const PlayerShot& shot);
}

namespace player {
    struct Player {
        bool alive;
        Rectangle sprite_rect;
        Vector2 pos;
        player_shot::PlayerShot shot;
        bool exploding;
        float explosion_timer;
    };

    void init(Player& player);
    void update(Player& player);
    void draw(const Player& player, const Texture& atlas);
    void explode(Player& player);
    Rectangle get_hitbox(const Player& player);
}
