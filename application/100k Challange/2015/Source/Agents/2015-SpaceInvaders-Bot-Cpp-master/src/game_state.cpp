#include "game_state.h"
#include <iostream>
#include <fstream>
#include <limits>

const int OPENING_LINES = 6;
const int GAME_AREA_LINES = 25;

void moveToNextChar(int &x, int &y, int &width, char &nextChar, std::istream &mapFile)
{
    if (nextChar == '\n')
    {
        x = 0;
        ++y;
    }
    else
    {
        x += width;
    }
    if (width > 1)
    {
        mapFile.ignore(width-1);
    }
    nextChar = mapFile.get();
}

GameState::GameState(std::istream &&mapFile)
{
    for (int i=0; i<OPENING_LINES; ++i)
    {
        mapFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    char nextChar = mapFile.get();
    for (int x=0, y=0, width=1;
         y < GAME_AREA_LINES && nextChar != EOF;
         moveToNextChar(x, y, width, nextChar, mapFile))
    {
        width = addEntity(x, y, nextChar);
    }
}

int GameState::addEntity(int x, int y, char type)
{
    switch (type)
    {
    case Alien::MAP_CHAR:
        _aliens.push_back(Alien(x,y));
        return 1;
    case EnemyBullet::ALIEN_MAP_CHAR:
    case EnemyBullet::ENEMY_MISSILE_MAP_CHAR:
        _bullets.push_back(EnemyBullet(x,y));
        return 1;
    case PlayerMissile::MAP_CHAR:
        _missiles.push_back(PlayerMissile(x,y));
        return 1;
    case Shield::MAP_CHAR:
        _shields.push_back(Shield(x,y));
        return 1;
    case Spaceship::ENEMY_MAP_CHAR:
    case Spaceship::PLAYER_MAP_CHAR:
        _spaceships.push_back(Spaceship(x+1,y));
        return 3;
    }
    return 1;
}

void GameState::logState()
{
    for (auto alien : _aliens)
    {
        std::cout << "Alien " << alien.coords() << std::endl;
    }
    for (auto bullet : _bullets)
    {
        std::cout << "Enemy Bullet" << bullet.coords() << std::endl;
    }
    for (auto missile : _missiles)
    {
        std::cout << "Player Missile" << missile.coords() << std::endl;
    }
    for (auto shield : _shields)
    {
        std::cout << "Shield" << shield.coords() << std::endl;
    }
    for (auto spaceship : _spaceships)
    {
        std::cout << "Spaceship" << spaceship.coords() << std::endl;
    }
}
