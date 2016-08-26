#pragma once

#include <string>

class GameEntity
{
public:
    GameEntity(int x, int y);
    int x() const {return _x;}
    int y() const {return _y;}

    std::string coords() const;
private:
    int _x;
    int _y;
};

