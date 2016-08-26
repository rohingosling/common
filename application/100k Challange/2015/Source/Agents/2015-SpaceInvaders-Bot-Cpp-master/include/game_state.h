#pragma once

#include "alien.h"
#include "enemy_bullet.h"
#include "player_missile.h"
#include "shield.h"
#include "spaceship.h"
#include <vector>
#include <string>
#include <istream>

class GameState
{
public:
    GameState(std::istream &&mapFile);
    void logState();

    const std::vector<Alien>& aliens() const { return _aliens; }
    const std::vector<EnemyBullet>& bullets() const { return _bullets; }
    const std::vector<PlayerMissile>& missiles() const { return _missiles; }
    const std::vector<Shield>& shields() const { return _shields; }
    const std::vector<Spaceship>& spaceships() const { return _spaceships; }
    
private:
    std::vector<Alien> _aliens;
    std::vector<EnemyBullet> _bullets;
    std::vector<PlayerMissile> _missiles;
    std::vector<Shield> _shields;
    std::vector<Spaceship> _spaceships;

    int addEntity(int x, int y, char type);
};
