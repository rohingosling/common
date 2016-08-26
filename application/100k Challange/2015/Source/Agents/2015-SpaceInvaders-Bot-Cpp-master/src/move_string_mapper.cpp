#include "move_string_mapper.h"

#include "move.h"
#include <map>
#include <string>

MoveStringMapper::MoveStringMapper()
{
    moveMap[Move::NOTHING] = "Nothing";
    moveMap[Move::MOVE_LEFT] = "MoveLeft";
    moveMap[Move::MOVE_RIGHT] = "MoveRight";
    moveMap[Move::SHOOT] = "Shoot";
    moveMap[Move::BUILD_ALIEN_FACTORY] = "BuildAlienFactory";
    moveMap[Move::BUILD_MISSILE_CONTROLLER] = "BuildMissileController";
    moveMap[Move::BUILD_SHIELD] = "BuildShield";    
}

std::string MoveStringMapper::toString(const Move &move)
{
    return moveMap[move];
}
