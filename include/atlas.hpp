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
        {28, 0, 12, 8},     // Crab1
        {40, 0, 12, 8},     // Crab2
        {52, 0, 12, 8},     // Octopus1
        {64, 0, 12, 8},     // Octopus2
        {76, 0, 15, 8},     // PlayerExplode1
        {91, 0, 16, 8},     // PlayerExplode2
        {107, 0, 13, 8},    // PlayerNormal
        {120, 0, 8, 8},     // PlayerShotExplode
        {86, 16, 1, 4},     // PlayerShotNormal
        {77, 16, 3, 6},     // PlungerShot1
        {80, 16, 3, 6},     // PlungerShot2
        {83, 16, 3, 6},     // PlungerShot3
        {74, 16, 3, 6},     // PlungerShot4
        {37, 16, 3, 7},     // RollingShot2
        {40, 16, 3, 7},     // RollingShot4
        {43, 16, 3, 7},     // RollingShot13
        {0, 0, 22, 16},     // Shield
        {13, 16, 12, 8},    // Squid1
        {25, 16, 12, 8},    // Squid2
        {46, 16, 3, 7},     // SquigglyShot1
        {49, 16, 3, 7},     // SquigglyShot2
        {52, 16, 3, 7},     // SquigglyShot3
        {55, 16, 3, 7},     // SquigglyShot4
        {58, 16, 16, 7}     // Ufo
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
