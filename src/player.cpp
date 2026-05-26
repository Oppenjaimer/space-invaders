#include "atlas.hpp"
#include "config.hpp"
#include "player.hpp"

void player::init(Player& player) {
    // Cannon
    player.sprite_rect = atlas::get_sprite_rect(atlas::PlayerNormal);
    player.pos = {
        config::world_width / 2.0f - player.sprite_rect.width,
        config::world_height - config::player_spacing_bottom - player.sprite_rect.height
    };

    // Shot
    player.shot_active = false;
    player.shot_rect = atlas::get_sprite_rect(atlas::PlayerShotNormal);
    player.shot_pos = {0, 0}; // Computed from player's position when shooting
}

void player::update(Player& player) {
    // Move cannon
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        player.pos.x -= config::player_speed;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        player.pos.x += config::player_speed;

    // Ensure player is within world bounds
    if (player.pos.x <= config::player_spacing_sides)
        player.pos.x = config::player_spacing_sides;
    else if (player.pos.x >= config::world_width - config::player_spacing_sides - player.sprite_rect.width)
        player.pos.x = config::world_width - config::player_spacing_sides - player.sprite_rect.width;

    // Shoot
    if (IsKeyPressed(KEY_SPACE) && !player.shot_active) {
        player.shot_active = true;
        player.shot_pos = {
            player.pos.x + player.sprite_rect.width / 2.0f - player.shot_rect.width / 2.0f,
            player.pos.y
        };
    }

    // Move shot
    if (player.shot_active)
        player.shot_pos.y -= config::player_shot_speed;

    // Deactivate shot when out of world bounds
    if (player.shot_active && player.shot_pos.y < 0)
        player.shot_active = false;
}

void player::draw(const Player& player, const Texture& atlas) {
    // Shot
    if (player.shot_active)
        DrawTextureRec(atlas, player.shot_rect, player.shot_pos, theme::fg0);

    // Cannon
    DrawTextureRec(atlas, player.sprite_rect, player.pos, theme::green);
}
