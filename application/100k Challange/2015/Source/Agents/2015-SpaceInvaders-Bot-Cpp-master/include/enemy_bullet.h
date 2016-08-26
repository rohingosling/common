#pragma once

#include "game_entity.h"

class EnemyBullet: public GameEntity
{
public:
    EnemyBullet(int x, int y);
    const static char ALIEN_MAP_CHAR = '|';
    const static char ENEMY_MISSILE_MAP_CHAR = 'i';
private:
};
