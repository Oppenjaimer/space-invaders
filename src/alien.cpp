#include "alien.hpp"
#include "atlas.hpp"

#include <vector>

static void set_sprite_rect(alien::Alien& alien) {
    // [Type][Frame]
    static const atlas::SpriteId alien_frames[][2] = {
        {atlas::Squid1,   atlas::Squid2},   // 0: Squid
        {atlas::Crab1,    atlas::Crab2},    // 1: Crab
        {atlas::Octopus1, atlas::Octopus2}  // 2: Octopus
    };

    alien.sprite_rect = atlas::get_sprite_rect(alien_frames[alien.type][alien.animation_frame]);
}

static void set_sprite_rect(alien_shot::AlienShot& shot) {
    // [Type][Frame]
    static const atlas::SpriteId shot_frames[][4] = {
        {atlas::PlungerShot1,  atlas::PlungerShot2,  atlas::PlungerShot3,  atlas::PlungerShot4},    // 0: Plunger
        {atlas::RollingShot13, atlas::RollingShot2,  atlas::RollingShot13, atlas::RollingShot4},    // 1: Rolling
        {atlas::SquigglyShot1, atlas::SquigglyShot2, atlas::SquigglyShot3, atlas::SquigglyShot4}    // 2: Squiggly
    };

    shot.sprite_rect = atlas::get_sprite_rect(shot_frames[shot.type][shot.animation_frame]);
}

static void fleet_move(fleet::Fleet& fleet, alien::AlienArray& aliens) {
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
}

static void fleet_fire(fleet::Fleet& fleet, alien::AlienArray& aliens, alien_shot::AlienShotArray& shots, float player_x_min, float player_x_max) {
    // Find available shot slot
    alien_shot::AlienShot* available_shot = nullptr;
    for (auto& shot : shots) {
        if (!shot.active && !shot.exploding) {
            available_shot = &shot;
            break;
        }
    }

    // No shot slots available
    if (available_shot == nullptr) return;

    // Get columns with alive aliens
    std::vector<int> active_cols;
    for (int j = 0; j < config::alien_cols; j++) {
        for (int i = 0; i < config::alien_rows; i++) {
            if (aliens[i * config::alien_cols + j].alive) {
                active_cols.push_back(j);
                break;
            }
        }
    }

    // No active columns found
    if (active_cols.empty()) return;

    // Pick random shot type
    alien_shot::ShotType type = static_cast<alien_shot::ShotType>(GetRandomValue(0, 2));

    int target_col = -1;
    if (type == alien_shot::Rolling) {
        // Choose column above player
        for (int col : active_cols) {
            for (int i = 0; i < config::alien_rows; i++) {
                // Find any alive alien to get the column position
                int idx = i * config::alien_cols + col;
                if (!aliens[idx].alive) continue;

                float alien_x_min = aliens[idx].pos.x;
                float alien_x_max = alien_x_min + aliens[idx].sprite_rect.width;

                // Check if alien column interval overlaps player interval
                if (alien_x_max >= player_x_min && alien_x_min <= player_x_max) {
                    target_col = col;
                    break;
                }

                // Checking the first alive alien in the column is enough
                break;
            }

            // Column above player already found
            if (target_col != -1) break;
        }

        if (target_col == -1) {
            // No column above player found, fallback to random column
            int random_idx = GetRandomValue(0, active_cols.size() - 1);
            target_col = active_cols[random_idx];
        }
    } else {
        // Pick random column
        int random_idx = GetRandomValue(0, active_cols.size() - 1);
        target_col = active_cols[random_idx];
    }

    // Find lowest alien in target column
    for (int i = config::alien_rows - 1; i >= 0; i--) {
        int idx = i * config::alien_cols + target_col;
        if (aliens[idx].alive) {
            float x = aliens[idx].pos.x + aliens[idx].sprite_rect.width / 2.0f - available_shot->sprite_rect.width / 2.0f;
            float y = aliens[idx].pos.y + aliens[idx].sprite_rect.height;

            alien_shot::fire(*available_shot, type, x, y);

            fleet.shot_timer = config::alien_shot_interval; // TODO: decrease shot interval with score
            break;
        }
    }
}

void alien::set_type(Alien& alien, AlienType type) {
    alien.type = type;
    set_sprite_rect(alien);
}

void alien::advance_frame(Alien& alien) {
    alien.animation_frame = (alien.animation_frame == 0) ? 1 : 0;
    set_sprite_rect(alien);
}

void alien::init(Alien& alien) {
    alien.animation_frame = 0;
    alien.pos = {0, 0}; // Computed when creating all aliens
    alien.alive = true;
    alien.exploding = false;
    alien.explosion_timer = 0.0f; // Set when hit
}

void alien::update(Alien& alien) {
    if (alien.exploding) {
        alien.explosion_timer -= GetFrameTime();

        if (alien.explosion_timer <= 0.0f)
            alien.exploding = false;
    }
}

void alien::draw(const Alien& alien, const Texture& atlas) {
    if (!alien.alive && !alien.exploding) return;

    Color color;
    switch (alien.type) {
        case Squid:   color = theme::purple; break;
        case Crab:    color = theme::blue;   break;
        case Octopus: color = theme::aqua;   break;
    }

    if (alien.exploding) {
        Rectangle explosion_rect = atlas::get_sprite_rect(atlas::AlienExplode);
        DrawTextureRec(atlas, explosion_rect, alien.pos, color);
    } else if (alien.alive) {
        DrawTextureRec(atlas, alien.sprite_rect, alien.pos, color);
    }
}

void alien::explode(Alien& alien) {
    if (alien.alive && !alien.exploding) {
        alien.alive = false;
        alien.exploding = true;
        alien.explosion_timer = config::explosion_time;
    }
}

Rectangle alien::get_hitbox(const Alien& alien) {
    if (!alien.alive || alien.exploding) return {0, 0, 0, 0};

    return {
        alien.pos.x,
        alien.pos.y,
        alien.sprite_rect.width,
        alien.sprite_rect.height
    };
}

void alien_shot::advance_frame(AlienShot &shot) {
    shot.animation_frame = (shot.animation_frame + 1) % 4;
    set_sprite_rect(shot);
}

void alien_shot::init(AlienShot &shot) {
    shot.active = false;
    shot.animation_frame = 0;
    shot.animation_timer = 0;
    shot.pos = {0, 0}; // Computed from alien's position when firing
    shot.exploding = false;
    shot.explosion_timer = 0.0f; // Set when hit
}

void alien_shot::update(AlienShot &shot) {
    // Move downwards
    if (shot.active)
        shot.pos.y += config::alien_shot_speed;

    // Deactivate shot when out of world bounds
    if (shot.active && shot.pos.y >= config::world_height) {
        shot.active = false;
        return;
    }

    // Animate shot
    shot.animation_timer += GetFrameTime();
    if (shot.animation_timer >= config::alien_shot_animation_rate) {
        advance_frame(shot);
        shot.animation_timer -= config::alien_shot_animation_rate;
    }

    // Explode
    if (shot.exploding) {
        shot.explosion_timer -= GetFrameTime();

        if (shot.explosion_timer <= 0.0f)
            shot.exploding = false;
    }
}

void alien_shot::draw(const AlienShot &shot, const Texture &atlas) {
    if (shot.exploding) {
        Rectangle explosion_rect = atlas::get_sprite_rect(atlas::AlienShotExplode);
        Vector2 pos = {
            shot.pos.x + shot.sprite_rect.width / 2.0f - explosion_rect.width / 2.0f,
            shot.pos.y + shot.sprite_rect.height - explosion_rect.height / 2.0f
        };

        DrawTextureRec(atlas, explosion_rect, pos, WHITE);
    } else if (shot.active) {
        DrawTextureRec(atlas, shot.sprite_rect, shot.pos, theme::fg0);
    }
}

void alien_shot::fire(AlienShot &shot, ShotType type, int x, int y) {
    if (shot.active) return;

    shot.type = type;
    shot.active = true;
    shot.animation_frame = 0;
    shot.pos.x = x;
    shot.pos.y = y;
    shot.exploding = false;
    shot.explosion_timer = 0.0f;

    set_sprite_rect(shot);
}

void alien_shot::explode(AlienShot& shot) {
    if (shot.active && !shot.exploding) {
        shot.active = false;
        shot.exploding = true;
        shot.explosion_timer = config::explosion_time;
    }
}

Rectangle alien_shot::get_hitbox(const AlienShot &shot) {
    return {
        shot.pos.x,
        shot.pos.y,
        shot.sprite_rect.width,
        shot.sprite_rect.height
    };
}

void fleet::init(Fleet& fleet) {
    fleet.shot_timer = config::alien_grace_period;
    fleet.move_timer = 0.0f;
    fleet.direction = 1;
}

void fleet::update(Fleet& fleet, alien::AlienArray& aliens, alien_shot::AlienShotArray& shots, float player_x_min, float player_x_max) {
    // Count alive aliens and time explosions
    int alive = 0;
    for (alien::Alien& alien : aliens) {
        alien::update(alien);
        if (alien.alive) alive++;
    }

    // Movement
    float move_interval = (float)alive * config::alien_move_interval;

    fleet.move_timer += GetFrameTime();
    if (fleet.move_timer >= move_interval) {
        fleet_move(fleet, aliens);
        fleet.move_timer -= move_interval;
    }

    // Firing
    fleet.shot_timer -= GetFrameTime();
    if (fleet.shot_timer <= 0)
        fleet_fire(fleet, aliens, shots, player_x_min, player_x_max);
}
