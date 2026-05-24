#include "raylib.h"

#include "config.hpp"
#include "game.hpp"

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

    // Initialize game state
    game::State state = {};
    game::init(state);

    while (!WindowShouldClose()) {
        // Logic
        game::update(state);

        // Draw to virtual world
        BeginTextureMode(state.target);
        ClearBackground(theme::bg0);
        game::draw_world(state);
        EndTextureMode();

        // Draw virtual world to screen
        BeginDrawing();
        ClearBackground(theme::bg0_hard);
        game::draw_screen(state);
        EndDrawing();
    }

    // Cleanup
    game::free(state);
    CloseWindow();

    return 0;
}
