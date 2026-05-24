#include "config.hpp"
#include "game.hpp"

/**
 * @brief Set raylib resources directory.
 * @param path Directory path.
 * @returns Whether the directory was found.
 */
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

void game::init(State &state) {
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

    // Initialize player
    player::init(state.player);
}

void game::free(State &state) {
    UnloadTexture(state.atlas);
    UnloadRenderTexture(state.target);
}

void game::update(State &state) {
    player::update(state.player);
}

void game::draw_world(const State &state) {
    player::draw(state.atlas, state.player);
}

void game::draw_screen(const State &state) {
    // Calculate scale to fit the window (keeping aspect ratio)
    float scale_x = (float)GetScreenWidth() / config::world_width;
    float scale_y = (float)GetScreenHeight() / config::world_height;
    float scale = (scale_x < scale_y) ? scale_x : scale_y;

    Rectangle src_rect = {0, 0, (float)state.target.texture.width, (float)-state.target.texture.height};
    Rectangle dest_rect = {
        (GetScreenWidth() - (config::world_width * scale)) / 2.0f,
        (GetScreenHeight() - (config::world_height * scale)) / 2.0f,
        config::world_width * scale,
        config::world_height * scale
    };

    DrawTexturePro(state.target.texture, src_rect, dest_rect, {0, 0}, 0, WHITE);
}
