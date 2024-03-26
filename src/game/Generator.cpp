#include "Generator.h"
#include "GameObject.h"
#include "Board.h"
#include "Blocks.h"
#include "Player.h"
#include "Level.h"
#include "PowerUp.h"

#include <iostream>


std::string Generator::create(bool isMultiplayer, int rows, int columns)
{
    Board* board = new Board(rows, columns);
    Player* player = new Player(0,0);
    board->addObject(player);
    if(isMultiplayer)
    {
        Player* player2 = new Player(0,0);
        board->addObject(player2);
    }
    int enemiesAdded = 0;
    Level l;
    for(int i = 0 ; i < rows; i++)
    {
        //because the player will always start at position 0,0 to j muxt start from 1
        for (int j = 1; j < columns; j++)
        {
            int randomNumber = rand()%4;
            if(randomNumber == 1)
            {
                Block* block = new Block (true, i, j, PowerUp::NO_POWERUP, board);
                board->addObject(block);
            }
            else if(randomNumber == 2)
            {
                Block* unbreackableBlock = new Block (false, i, j, PowerUp::NO_POWERUP, board);
                board->addObject(unbreackableBlock);
            }
            else if(randomNumber == 3 && !isMultiplayer && enemiesAdded < maxEnemies)
            {
                Player* enemy = new Player(i,j);
                enemy->setEnemy(true);
                board->addObject(enemy);
                enemiesAdded++;
            }
        }
    }
    std::string result = l.serialize(*board);
    return result;

}
