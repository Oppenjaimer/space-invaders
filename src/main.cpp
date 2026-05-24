#include "raylib.h"

#include "atlas.hpp"
#include "config.hpp"

/**
 * @brief Set raylib resources directory.
 * @param path Directory path.
 * @returns Whether the directory was found.
 */
bool set_resource_dir(const char* path) {
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

/**
 * @brief Application entry point.
 * @returns Exit code.
 */
int main() {
    // Initialize raylib
    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(config::screen_width, config::screen_height, config::title);
    SetTargetFPS(config::fps);

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
    RenderTexture target = LoadRenderTexture(config::world_width, config::world_height);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

    // Load sprites atlas
    Texture atlas = LoadTexture(config::atlas_file);
    Rectangle shield_rect = atlas::get_sprite_rect(atlas::Shield);

    while (!WindowShouldClose()) {
        // Logic
        // ...

        // Draw within virtual world
        BeginTextureMode(target);
        ClearBackground(theme::bg0);
        DrawTextureRec(atlas, shield_rect, {10, 10}, theme::green);
        EndTextureMode();

        // Draw virtual world to screen
        BeginDrawing();
        ClearBackground(theme::bg0_hard);

        // Calculate scale to fit the window (keeping aspect ratio)
        float scale_x = (float)GetScreenWidth() / config::world_width;
        float scale_y = (float)GetScreenHeight() / config::world_height;
        float scale = (scale_x < scale_y) ? scale_x : scale_y;

        Rectangle src_rect = {0, 0, (float)target.texture.width, (float)-target.texture.height};
        Rectangle dest_rect = {
            (GetScreenWidth() - (config::world_width * scale)) / 2.0f,
            (GetScreenHeight() - (config::world_height * scale)) / 2.0f,
            config::world_width * scale,
            config::world_height * scale
        };

        DrawTexturePro(target.texture, src_rect, dest_rect, {0, 0}, 0, WHITE);
        EndDrawing();
    }

    // Cleanup
    UnloadTexture(atlas);
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}
