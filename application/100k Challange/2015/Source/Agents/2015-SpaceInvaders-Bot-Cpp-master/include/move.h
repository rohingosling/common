#pragma once

enum class Move: int
{
    NOTHING = 0,
    MOVE_LEFT = 1,
    MOVE_RIGHT = 2,
    SHOOT = 3,
    BUILD_ALIEN_FACTORY = 4,
    BUILD_MISSILE_CONTROLLER = 5,
    BUILD_SHIELD = 6
};
