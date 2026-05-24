#pragma once

#include "raylib.h"

/**
 * @brief Sprites atlas handling.
 */
namespace atlas {
    enum SpriteId {
        AlienExplode,
        AlienShotExplode,
        Crab1,
        Crab2,
        Octopus1,
        Octopus2,
        PlayerExplode1,
        PlayerExplode2,
        PlayerNormal,
        PlayerShotExplode,
        PlayerShotNormal,
        PlungerShot1,
        PlungerShot2,
        PlungerShot3,
        PlungerShot4,
        RollingShot2,
        RollingShot4,
        RollingShot13,
        Shield,
        Squid1,
        Squid2,
        SquigglyShot1,
        SquigglyShot2,
        SquigglyShot3,
        SquigglyShot4,
        Ufo,
        Count
    };

    inline constexpr Rectangle sprites[Count] = {
        {0, 16, 13, 8},     // AlienExplode
        {22, 0, 6, 8},      // AlienShotExplode
        {28, 0, 11, 8},     // Crab1
        {39, 0, 11, 8},     // Crab2
        {50, 0, 12, 8},     // Octopus1
        {62, 0, 12, 8},     // Octopus2
        {74, 0, 15, 8},     // PlayerExplode1
        {89, 0, 16, 8},     // PlayerExplode2
        {105, 0, 13, 8},    // PlayerNormal
        {118, 0, 8, 8},     // PlayerShotExplode
        {78, 16, 1, 4},     // PlayerShotNormal
        {69, 16, 3, 6},     // PlungerShot1
        {72, 16, 3, 6},     // PlungerShot2
        {75, 16, 3, 6},     // PlungerShot3
        {66, 16, 3, 6},     // PlungerShot4
        {29, 16, 3, 7},     // RollingShot2
        {32, 16, 3, 7},     // RollingShot4
        {35, 16, 3, 7},     // RollingShot13
        {0, 0, 22, 16},     // Shield
        {13, 16, 8, 8},     // Squid1
        {21, 16, 8, 8},     // Squid2
        {38, 16, 3, 7},     // SquigglyShot1
        {41, 16, 3, 7},     // SquigglyShot2
        {44, 16, 3, 7},     // SquigglyShot3
        {47, 16, 3, 7},     // SquigglyShot4
        {50, 16, 16, 7},    // Ufo
    };

    /**
     * @brief Get sprite rectangle from atlas.
     * @param id Sprite ID.
     * @return Sprite rectangle.
     */
    inline constexpr Rectangle get_sprite_rect(SpriteId id) {
        return sprites[static_cast<int>(id)];
    }
}
