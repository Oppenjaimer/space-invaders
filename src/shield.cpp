#include "atlas.hpp"
#include "shield.hpp"

#include <cmath>

// Explosion mask dimensions and arrays
static constexpr int player_mask_w = 8;
static constexpr int player_mask_h = 8;
static bool player_explosion_mask[player_mask_h][player_mask_w];

static constexpr int alien_mask_w = 6;
static constexpr int alien_mask_h = 8;
static bool alien_explosion_mask[alien_mask_h][alien_mask_w];

static bool masks_loaded = false;

void shield::init(Shield& shield, const Image& atlas) {
    // Load explosion masks once for all shields
    if (!masks_loaded) {
        // Player mask
        Rectangle player_rect = atlas::get_sprite_rect(atlas::PlayerShotExplode);
        Image player_image = ImageFromImage(atlas, player_rect);

        for (int y = 0; y < player_mask_h; y++) {
            for (int x = 0; x < player_mask_w; x++) {
                Color pixel = GetImageColor(player_image, x, y);
                player_explosion_mask[y][x] = (pixel.a > 0);
            }
        }

        UnloadImage(player_image);

        // Alien mask
        Rectangle alien_rect = atlas::get_sprite_rect(atlas::AlienShotExplode);
        Image alien_image = ImageFromImage(atlas, alien_rect);

        for (int y = 0; y < alien_mask_h; y++) {
            for (int x = 0; x < alien_mask_w; x++) {
                Color pixel = GetImageColor(alien_image, x, y);
                alien_explosion_mask[y][x] = (pixel.a > 0);
            }
        }

        UnloadImage(alien_image);

        masks_loaded = true;
    }

    shield.pos = {0, 0}; // Computed when creating all shields

    Rectangle src_rect = atlas::get_sprite_rect(atlas::Shield);
    shield.image = ImageFromImage(atlas, src_rect);
    shield.texture = LoadTextureFromImage(shield.image);
}

void shield::free(Shield& shield) {
    UnloadImage(shield.image);
    UnloadTexture(shield.texture);
}

void shield::update(Shield& shield) {
    (void)shield;
}

void shield::draw(const Shield& shield) {
    DrawTextureV(shield.texture, shield.pos, theme::yellow);
}

Rectangle shield::get_hitbox(const Shield& shield) {
    return {
        shield.pos.x,
        shield.pos.y,
        (float)shield.texture.width,
        (float)shield.texture.height
    };
}

bool shield::apply_damage(Shield& shield, Rectangle shot_hitbox, bool shot_moving_up) {
    Rectangle shield_hitbox = get_hitbox(shield);
    Rectangle overlap = GetCollisionRec(shield_hitbox, shot_hitbox);

    // Convert overlap area to local shield coordinates
    int start_x = (int)(overlap.x - shield.pos.x);
    int start_y = (int)(overlap.y - shield.pos.y);
    int end_x = std::ceil(overlap.x + overlap.width - shield.pos.x);
    int end_y = std::ceil(overlap.y + overlap.height - shield.pos.y);

    bool hit = false;
    int hit_x = 0;
    int hit_y = 0;

    // Check pixels inside overlap area
    if (shot_moving_up) {
        for (int y = end_y - 1; y >= start_y; y--) {
            for (int x = start_x; x < end_x; x++) {
                if (x < 0 || x >= shield.image.width || y < 0 || y >= shield.image.height) continue;

                if (GetImageColor(shield.image, x, y).a > 0) {
                    hit = true;
                    hit_x = x;
                    hit_y = y;
                    break;
                }
            }

            if (hit) break;
        }
    } else {
        for (int y = start_y; y < end_y; y++) {
            for (int x = start_x; x < end_x; x++) {
                if (x < 0 || x >= shield.image.width || y < 0 || y >= shield.image.height) continue;

                if (GetImageColor(shield.image, x, y).a > 0) {
                    hit = true;
                    hit_x = x;
                    hit_y = y;
                    break;
                }
            }

            if (hit) break;
        }
    }

    // Empty overlap pixels
    if (!hit) return false;

    int mask_w = shot_moving_up ? player_mask_w : alien_mask_w;
    int mask_h = shot_moving_up ? player_mask_h : alien_mask_h;

    // Apply explosion mask
    int mask_x = hit_x - mask_w / 2;
    int mask_y = hit_y - mask_h / 2;

    for (int y = 0; y < mask_h; y++) {
        for (int x = 0; x < mask_w; x++) {
            bool is_solid_pixel = shot_moving_up ? player_explosion_mask[y][x] : alien_explosion_mask[y][x];
            if (!is_solid_pixel) continue;

            int target_x = mask_x + x;
            int target_y = mask_y + y;

            if (target_x >= 0 && target_x < shield.image.width && target_y >= 0 && target_y < shield.image.height)
                ImageDrawPixel(&shield.image, target_x, target_y, BLANK);
        }
    }

    UpdateTexture(shield.texture, shield.image.data);
    return true;
}

void shield::apply_alien_overlap(Shield& shield, Rectangle alien_hitbox) {
    Rectangle shield_hitbox = get_hitbox(shield);
    Rectangle overlap = GetCollisionRec(shield_hitbox, alien_hitbox);

    if (overlap.width == 0 && overlap.height == 0) return;

    // Convert overlap area to local shield coordinates
    int start_x = (int)(overlap.x - shield.pos.x);
    int start_y = (int)(overlap.y - shield.pos.y);
    int end_x = (int)std::ceil(overlap.x + overlap.width - shield.pos.x);
    int end_y = (int)std::ceil(overlap.y + overlap.height - shield.pos.y);

    bool modified = false;

    // Delete pixels within overlap area
    for (int y = start_y; y < end_y; y++) {
        for (int x = start_x; x < end_x; x++) {
            if (x < 0 || x >= shield.image.width || y < 0 || y >= shield.image.height) continue;

            if (GetImageColor(shield.image, x, y).a > 0) {
                ImageDrawPixel(&shield.image, x, y, BLANK);
                modified = true;
            }
        }
    }

    if (modified)
        UpdateTexture(shield.texture, shield.image.data);
}
