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
    bool found = set_resource_dir("resources");
    if (found) {
        Image icon = LoadImage("icon.png");
        SetWindowIcon(icon);
        UnloadImage(icon);
    } else {
        TraceLog(LOG_WARNING, "Unable to set resources directory");
    }

    // Load sprites atlas
    Texture atlas = LoadTexture(atlas::image_path);
    Rectangle shield_rect = atlas::get_sprite_rect("shield");

    while (!WindowShouldClose()) {
        // Logic
        // ...

        BeginDrawing();
        ClearBackground(theme::bg0);

        // Draw
        DrawTextureRec(atlas, shield_rect, {400, 500}, WHITE);

        EndDrawing();
    }

    // Cleanup
    CloseWindow();

    return 0;
}
