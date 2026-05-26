#include "atlas.hpp"
#include "config.hpp"
#include "player.hpp"

void player::init(Player& player) {
    player.sprite_rect = atlas::get_sprite_rect(atlas::PlayerNormal);
    player.pos = {
        config::world_width / 2.0f - player.sprite_rect.width,
        config::world_height - config::player_spacing_bottom - player.sprite_rect.height
    };

    player_shot::init(player.shot);
}

void player::update(Player& player) {
    // Move horizontally
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        player.pos.x -= config::player_speed;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        player.pos.x += config::player_speed;

    // Ensure player is within world bounds
    if (player.pos.x <= config::player_spacing_sides)
        player.pos.x = config::player_spacing_sides;
    else if (player.pos.x >= config::world_width - config::player_spacing_sides - player.sprite_rect.width)
        player.pos.x = config::world_width - config::player_spacing_sides - player.sprite_rect.width;

    // Fire shot
    if (IsKeyPressed(KEY_SPACE))
        player_shot::fire(
            player.shot,
            player.pos.x + player.sprite_rect.width / 2.0f - player.shot.sprite_rect.width / 2.0f,
            player.pos.y
        );

    player_shot::update(player.shot);
}

void player::draw(const Player& player, const Texture& atlas) {
    DrawTextureRec(atlas, player.sprite_rect, player.pos, theme::green);
    player_shot::draw(player.shot, atlas);
}

void player_shot::init(PlayerShot &shot) {
    shot.active = false;
    shot.sprite_rect = atlas::get_sprite_rect(atlas::PlayerShotNormal);
    shot.pos = {0, 0}; // Computed from player's position when firing
}

void player_shot::update(PlayerShot &shot) {
    // Move upwards
    if (shot.active)
        shot.pos.y -= config::player_shot_speed;

    // Deactivate shot when out of world bounds
    if (shot.active && shot.pos.y < 0)
        shot.active = false;
}

void player_shot::draw(const PlayerShot &shot, const Texture &atlas) {
    if (shot.active)
        DrawTextureRec(atlas, shot.sprite_rect, shot.pos, theme::fg0);
}

void player_shot::fire(PlayerShot &shot, int x, int y) {
    if (shot.active) return;

    shot.active = true;
    shot.pos.x = x;
    shot.pos.y = y;
}
