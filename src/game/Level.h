#pragma once

#include <tinyxml2.h>
#include <iostream>
#include "Board.h"

class Level
{
    public:
    std::string serialize(const Board& Board);
    bool deserialize(const std::string &xmlText, Board& b, std::vector<Player*> &players);

    private:
    bool setRamdomPowerUp = true;

};



