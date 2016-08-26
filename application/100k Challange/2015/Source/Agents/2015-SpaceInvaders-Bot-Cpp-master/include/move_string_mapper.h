#pragma once

#include <string>
#include <map>
#include "move.h"

class MoveStringMapper
{
public:
    MoveStringMapper();
    std::string toString(const Move &move);
private:
    std::map<Move, const char*> moveMap;
};
