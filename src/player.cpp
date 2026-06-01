#include "atlas.hpp"
#include "config.hpp"
#include "player.hpp"

void player::init(Player& player) {
    player.alive = true;
    player.sprite_rect = atlas::get_sprite_rect(atlas::PlayerNormal);
    player.pos = {
        config::world_width / 2.0f - player.sprite_rect.width,
        config::world_height - config::player_spacing_bottom - player.sprite_rect.height
    };

    player_shot::init(player.shot);

    player.exploding = false;
    player.explosion_timer = 0.0f; // Set when hit
}

void player::update(Player& player) {
    // Explode
    if (player.exploding) {
        player.explosion_timer -= GetFrameTime();

        if (player.explosion_timer <= 0.0f)
            player.exploding = false;
    }

    if (!player.alive) return;

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
    if (player.exploding) {
        int frame_toggle = (int)(player.explosion_timer / config::player_flash_time) % 2;
        Rectangle explosion_rect = atlas::get_sprite_rect(frame_toggle ? atlas::PlayerExplode1 : atlas::PlayerExplode2);
        DrawTextureRec(atlas, explosion_rect, player.pos, theme::green);
    } else if (player.alive) {
        DrawTextureRec(atlas, player.sprite_rect, player.pos, theme::green);
    }

    player_shot::draw(player.shot, atlas);
}

void player::explode(Player& player) {
    if (player.alive && !player.exploding) {
        player.alive = false;
        player.shot.active = false;
        player.exploding = true;
        player.shot.exploding = false;
        player.explosion_timer = config::player_explosion_time;
    }
}

Rectangle player::get_hitbox(const Player &player) {
    return {
        player.pos.x,
        player.pos.y,
        player.sprite_rect.width,
        player.sprite_rect.height
    };
}

void player_shot::init(PlayerShot& shot) {
    shot.active = false;
    shot.sprite_rect = atlas::get_sprite_rect(atlas::PlayerShotNormal);
    shot.pos = {0, 0}; // Computed from player's position when firing
    shot.exploding = false;
    shot.explosion_timer = 0.0f; // Set when hit
}

void player_shot::update(PlayerShot& shot) {
    // Move upwards
    if (shot.active)
        shot.pos.y -= config::player_shot_speed;

    // Deactivate shot when out of world bounds
    if (shot.active && shot.pos.y < 0)
        shot.active = false;

    // Explode
    if (shot.exploding) {
        shot.explosion_timer -= GetFrameTime();

        if (shot.explosion_timer <= 0.0f)
            shot.exploding = false;
    }
}

void player_shot::draw(const PlayerShot& shot, const Texture &atlas) {
    if (shot.exploding) {
        Rectangle explosion_rect = atlas::get_sprite_rect(atlas::PlayerShotExplode);
        Vector2 pos = {shot.pos.x - explosion_rect.width / 2.0f, shot.pos.y - explosion_rect.height / 2.0f};
        DrawTextureRec(atlas, explosion_rect, pos, WHITE);
    } else if (shot.active) {
        DrawTextureRec(atlas, shot.sprite_rect, shot.pos, theme::fg0);
    }
}

void player_shot::fire(PlayerShot& shot, int x, int y) {
    if (shot.active || shot.exploding) return;

    shot.active = true;
    shot.pos.x = x;
    shot.pos.y = y;
}

void player_shot::explode(PlayerShot& shot) {
    if (shot.active && !shot.exploding) {
        shot.active = false;
        shot.exploding = true;
        shot.explosion_timer = config::explosion_time;
    }
}

Rectangle player_shot::get_hitbox(const PlayerShot& shot) {
    return {
        shot.pos.x,
        shot.pos.y,
        shot.sprite_rect.width,
        shot.sprite_rect.height
    };
}
