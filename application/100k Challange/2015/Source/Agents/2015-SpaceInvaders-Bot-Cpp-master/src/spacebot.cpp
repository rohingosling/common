#include "spacebot.h"
#include "move_string_mapper.h"
#include <random>
#include <fstream>

Spacebot::Spacebot(std::string outputPath)
    : outputFilename(outputPath+"/move.txt"),
      gameState(std::ifstream(outputPath+"/map.txt"))
{
}

void Spacebot::writeNextMove()
{
    Move move = chooseMove();
    writeMove(move);
}

Move Spacebot::chooseMove()
{
    int min = static_cast<int>(Move::NOTHING);
    int max = static_cast<int>(Move::BUILD_SHIELD);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return static_cast<Move>(dis(gen));
}

void Spacebot::writeMove(const Move& move)
{
    std::ofstream resultStream(outputFilename);
    resultStream << MoveStringMapper().toString(move) << std::endl;
    return;
}

