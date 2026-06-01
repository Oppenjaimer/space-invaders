#include "config.hpp"
#include "game.hpp"

static bool set_resource_dir(const char* path) {
    // Check current directory
    if (DirectoryExists(path)) {
        ChangeDirectory(TextFormat("%s/%s", GetWorkingDirectory(), path));
        return true;
    }

    const char* app_dir = GetApplicationDirectory();

    // Check app directory
    const char* dir = TextFormat("%s%s", app_dir, path);
    if (DirectoryExists(dir)) {
        ChangeDirectory(dir);
        return true;
    }

    // Check one level up from app directory
    dir = TextFormat("%s../%s", app_dir, path);
    if (DirectoryExists(dir)) {
        ChangeDirectory(dir);
        return true;
    }

    // Check two levels up from app directory
    dir = TextFormat("%s../../%s", app_dir, path);
    if (DirectoryExists(dir)) {
        ChangeDirectory(dir);
        return true;
    }

    return false;
}

static void check_collisions(game::State& state) {
    Rectangle player_hitbox = player::get_hitbox(state.player);
    Rectangle player_shot_hitbox = player_shot::get_hitbox(state.player.shot);

    // Aliens
    for (auto& alien : state.aliens) {
        if (!alien.alive || alien.exploding) continue;
        Rectangle alien_hitbox = alien::get_hitbox(alien);

        // Player shot hitting aliens
        if (state.player.shot.active && CheckCollisionRecs(player_shot_hitbox, alien_hitbox)) {
            state.player.shot.active = false;
            alien::explode(alien);
        }

        // Alien hitting shields
        for (auto& shield : state.shields) {
            Rectangle shield_hitbox = shield::get_hitbox(shield);
            if (CheckCollisionRecs(alien_hitbox, shield_hitbox))
                shield::apply_alien_overlap(shield, alien_hitbox);
        }
    }

    // Player shot hitting UFO
    Rectangle ufo_hitbox = ufo::get_hitbox(state.ufo);
    if (state.player.shot.active && CheckCollisionRecs(player_shot_hitbox, ufo_hitbox)) {
        state.player.shot.active = false;
        state.ufo.alive = false;
    }

    // Alien shots
    for (auto& shot : state.alien_shots) {
        if (!shot.active) continue;
        Rectangle alien_shot_hitbox = alien_shot::get_hitbox(shot);

        // Player shot hitting alien shot
        if (state.player.shot.active && CheckCollisionRecs(player_shot_hitbox, alien_shot_hitbox)) {
            state.player.shot.active = false;
            alien_shot::explode(shot);
        }

        // Alien shot hitting player
        if (state.player.alive && CheckCollisionRecs(alien_shot_hitbox, player_hitbox)) {
            shot.active = false;
            player::explode(state.player);
            // TODO: game over
        }

        // Alien shot hitting shields
        for (auto& shield : state.shields) {
            Rectangle shield_hitbox = shield::get_hitbox(shield);
            if (CheckCollisionRecs(alien_shot_hitbox, shield_hitbox)) {
                if (shield::apply_damage(shield, alien_shot_hitbox, false)) {
                    alien_shot::explode(shot);
                    break;
                }
            }
        }
    }

    // Player shot hitting shields
    for (auto& shield : state.shields) {
        Rectangle shield_hitbox = shield::get_hitbox(shield);
        if (CheckCollisionRecs(player_shot_hitbox, shield_hitbox)) {
            if (shield::apply_damage(shield, player_shot_hitbox, true)) {
                player_shot::explode(state.player.shot);
                break;
            }
        }
    }
}

void game::init(State& state) {
    // Set resources directory and app icon
    bool found = set_resource_dir(config::resource_dir);
    if (found) {
        Image icon = LoadImage(config::icon_file);
        SetWindowIcon(icon);
        UnloadImage(icon);
    } else {
        TraceLog(LOG_WARNING, "Unable to set resources directory");
    }

    // Load render texture for virtual world
    state.target = LoadRenderTexture(config::world_width, config::world_height);
    SetTextureFilter(state.target.texture, TEXTURE_FILTER_POINT);

    // Load sprites atlas
    state.atlas = LoadTexture(config::atlas_file);
    Image atlas_image = LoadImage(config::atlas_file);

    // Initialize player
    player::init(state.player);

    // Initialize shields
    shield::Shield shield;
    shield::init(shield, atlas_image);

    for (int i = 0; i < config::shield_count; i++) {
        shield::init(state.shields[i], atlas_image);
        state.shields[i].pos.x = config::shield_spacing_left + i * (config::shield_spacing_inner + shield.texture.width);
        state.shields[i].pos.y = config::world_height - config::shield_spacing_bottom - shield.texture.height;
    }

    // Free shield template
    shield::free(shield);
    UnloadImage(atlas_image);

    // Initialize aliens
    alien::Alien alien;
    alien::init(alien);

    for (int i = 0; i < config::alien_rows; i++) {
        for (int j = 0; j < config::alien_cols; j++) {
            // Choose alien type depending on row
            if (i == 0) alien::set_type(alien, alien::Squid);
            else if (i == 1 || i == 2) alien::set_type(alien, alien::Crab);
            else if (i == 3 || i == 4) alien::set_type(alien, alien::Octopus);

            alien.pos.x = config::alien_spacing_sides + j * (config::alien_spacing_inner_x + alien.sprite_rect.width);
            alien.pos.y = config::alien_spacing_top + i * (config::alien_spacing_inner_y + alien.sprite_rect.height);
            state.aliens[i * config::alien_cols + j] = alien;
        }
    }

    // Initialize alien shots
    for (auto& shot : state.alien_shots) {
        alien_shot::init(shot);
    }

    // Initialize alien fleet
    fleet::init(state.fleet);

    // Initialize UFO
    ufo::init(state.ufo);
}

void game::free(State& state) {
    for (auto& shield : state.shields) {
        shield::free(shield);
    }

    UnloadTexture(state.atlas);
    UnloadRenderTexture(state.target);
}

void game::update(State& state) {
    player::update(state.player);

    for (auto& shield : state.shields) {
        shield::update(shield);
    }

    for (auto& alien : state.aliens) {
        alien::update(alien);
    }

    for (auto& shot : state.alien_shots) {
        alien_shot::update(shot);
    }

    float player_x_min = state.player.pos.x;
    float player_x_max = player_x_min + state.player.sprite_rect.width;
    fleet::update(state.fleet, state.aliens, state.alien_shots, player_x_min, player_x_max);

    ufo::update(state.ufo);

    check_collisions(state);
}

void game::draw_world(const State& state) {
    player::draw(state.player, state.atlas);

    for (auto& shield : state.shields) {
        shield::draw(shield);
    }

    for (auto& alien : state.aliens) {
        alien::draw(alien, state.atlas);
    }

    for (auto& shot : state.alien_shots) {
        alien_shot::draw(shot, state.atlas);
    }

    ufo::draw(state.ufo, state.atlas);
}

void game::draw_screen(const State& state) {
    // Calculate scale to fit the window (keeping aspect ratio)
    float scale_x = (float)GetScreenWidth() / config::world_width;
    float scale_y = (float)GetScreenHeight() / config::world_height;

    int scale = (scale_x < scale_y) ? scale_x : scale_y;
    if (scale < 1) scale = 1;

    Rectangle src_rect = {0, 0, (float)state.target.texture.width, (float)-state.target.texture.height};
    Rectangle dest_rect = {
        (GetScreenWidth() - (config::world_width * scale)) / 2.0f,
        (GetScreenHeight() - (config::world_height * scale)) / 2.0f,
        config::world_width * (float)scale,
        config::world_height * (float)scale
    };

    DrawTexturePro(state.target.texture, src_rect, dest_rect, {0, 0}, 0, WHITE);
}
