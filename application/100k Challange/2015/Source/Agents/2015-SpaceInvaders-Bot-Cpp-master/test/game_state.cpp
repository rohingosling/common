#include "catch.hpp"
#include <sstream>

#include "game_state.h"

SCENARIO("game state is read from istream")
{
    GIVEN("a valid map file")
    {
        std::stringstream file;
        file << "###################" << std::endl;
        file << "# Node Sample Bot #" << std::endl;
        file << "# Round:   1      #" << std::endl;
        file << "# Kills: 0        #" << std::endl;
        file << "# Lives: 2        #" << std::endl;
        file << "# Missiles: 0/1   #" << std::endl;
        file << "###################" << std::endl;
        file << "#                 #" << std::endl;
        file << "#       VVV       #" << std::endl;
        file << "# ---         --- #" << std::endl;
        file << "# ---         --- #" << std::endl;
        file << "# ---    i    --- #" << std::endl;
        file << "#                 #" << std::endl;
        file << "#                 #" << std::endl;
        file << "#                 #" << std::endl;
        file << "#                 #" << std::endl;
        file << "#                 #" << std::endl;
        file << "#         x  x  x #" << std::endl;
        file << "#                 #" << std::endl;
        file << "#         x  x  x #" << std::endl;
        file << "#                 #" << std::endl;
        file << "#         |       #" << std::endl;
        file << "#                 #" << std::endl;
        file << "#                 #" << std::endl;
        file << "#          !      #" << std::endl;
        file << "# ---         --- #" << std::endl;
        file << "# ---         --- #" << std::endl;
        file << "# ---         --- #" << std::endl;
        file << "#       AAA       #" << std::endl;
        file << "#                 #" << std::endl;
        file << "###################" << std::endl;
        file << "# Missiles: 0/1   #" << std::endl;
        file << "# Lives: 2        #" << std::endl;
        file << "# Kills: 0        #" << std::endl;
        file << "# Round:   1      #" << std::endl;
        file << "# Node Sample Bot #" << std::endl;
        file << "###################" << std::endl;
        
        WHEN ("the game state is initilized")
        {
            GameState state(std::move(file));
            
            THEN("the aliens are read correctly")
            {
                auto aliens = state.aliens();
                REQUIRE(aliens.size() == 6);
                REQUIRE(aliens[0].x() == 10);
                REQUIRE(aliens[0].y() == 11);
                REQUIRE(aliens[5].x() == 16);
                REQUIRE(aliens[5].y() == 13);
            }

            THEN("the shields are read correctly")
            {
                auto shields = state.shields();
                REQUIRE(shields.size() == 36);
            }

            THEN("the enemy bullets are read correctly")
            {
                auto bullets = state.bullets();
                REQUIRE(bullets.size() == 2);
            }

            THEN("the player missiles are read correctly")
            {
                auto missiles = state.missiles();
                REQUIRE(missiles.size() == 1);
                REQUIRE(missiles[0].x() == 11);
                REQUIRE(missiles[0].y() == 18);
            }

            THEN("the spaceships are read correctly")
            {
                auto spaceships = state.spaceships();
                REQUIRE(spaceships.size() == 2);
            }
        }
    }
}
