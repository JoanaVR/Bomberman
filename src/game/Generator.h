#pragma once
#include <iostream>

class Generator
{
    public:
    std::string create(bool isMultiplayer, int rows, int columns);

    private:
    int maxEnemies = 3;
};