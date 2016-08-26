#include "game_entity.h"
#include <sstream>

GameEntity::GameEntity(int x, int y)
    :_x(x), _y(y)
{}

std::string GameEntity::coords() const
{
    std::stringstream ss;
    ss << "(" << _x << ", " << _y << ")";
    return ss.str();
}
