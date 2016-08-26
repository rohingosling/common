#pragma once

#include "game_entity.h"

class PlayerMissile: public GameEntity
{
public:
    PlayerMissile(int x, int y);
    const static char MAP_CHAR = '!';
private:
};
