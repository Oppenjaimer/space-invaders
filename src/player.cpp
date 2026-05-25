
#include "atlas.hpp"
#include "config.hpp"
#include "player.hpp"

void player::init(Player& player) {
    player.sprite_rect = atlas::get_sprite_rect(atlas::PlayerNormal);
    player.pos = {
        config::world_width / 2.0f - player.sprite_rect.width,
        config::world_height - config::player_spacing_y - player.sprite_rect.height
    };

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
    if (player.pos.x <= config::player_spacing_x)
        player.pos.x = config::player_spacing_x;
    else if (player.pos.x >= config::world_width - config::player_spacing_x - player.sprite_rect.width)
        player.pos.x = config::world_width - config::player_spacing_x - player.sprite_rect.width;

    // Shoot
    if (IsKeyDown(KEY_SPACE) && !player.shot_active) {
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

void player::draw(Texture atlas, const Player& player) {
    // Draw shot
    if (player.shot_active)
        DrawTextureRec(atlas, player.shot_rect, player.shot_pos, theme::fg0);

    // Draw cannon
    DrawTextureRec(atlas, player.sprite_rect, player.pos, theme::green);
}
