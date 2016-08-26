#include "catch.hpp"
#include "move.h"
#include <string>
#include "move_string_mapper.h"

SCENARIO("Writing a move")
{
    GIVEN("A Move")
    {
        Move move = Move::MOVE_LEFT;

        WHEN("It is mapped to a string")
        {
            std::string moveString = MoveStringMapper().toString(move);

            THEN("The string is correct")
            {
                REQUIRE(moveString == "MoveLeft");
            }
        }
        
    }
}
