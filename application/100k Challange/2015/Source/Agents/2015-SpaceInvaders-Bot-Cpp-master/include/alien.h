#pragma once

#include "game_entity.h"

class Alien : public GameEntity
{
public:
    Alien(int x, int y);
    const static char MAP_CHAR = 'x';
private:
};
