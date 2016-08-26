#pragma once

#include "game_entity.h"

class Spaceship: public GameEntity
{
public:
    Spaceship(int x, int y);
    const static char ENEMY_MAP_CHAR = 'V';
    const static char PLAYER_MAP_CHAR = 'A';
private:
};
