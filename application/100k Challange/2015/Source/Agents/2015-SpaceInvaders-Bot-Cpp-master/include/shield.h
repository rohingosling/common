#pragma once

#include "game_entity.h"

class Shield: public GameEntity
{
public:
    Shield(int x, int y);
    const static char MAP_CHAR = '-';
private:
};

