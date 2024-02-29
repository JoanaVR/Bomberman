#pragma once

#include <tinyxml2.h>
#include <iostream>
#include "Board.h"

class Level
{
    public:
    std::string serialize(const Board& Board);
    bool deserialize(std::string& filename, Board& b);


};



