
#include "atlas.hpp"
#include "config.hpp"
#include "player.hpp"

void player::init(Player& player) {
    player.sprite_rect = atlas::get_sprite_rect(atlas::PlayerNormal);
    player.pos = {
        config::world_width / 2.0f - player.sprite_rect.width,
        config::world_height - config::player_spacing_y - player.sprite_rect.height
    };
}

void player::update(Player& player) {
    // Move
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
    // TODO
}

void player::draw(Texture atlas, const Player& player) {
    DrawTextureRec(atlas, player.sprite_rect, player.pos, theme::green);
}
