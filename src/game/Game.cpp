#include "Game.h"
#include "Level.h"
#include "Board.h"

#include <Logging.h>

#include <map>

Game::Game(const std::string &level, std::function<void()> onGameOver)
{
    mOnGameOver = onGameOver;
    Level l;
    mBoard = new Board(1, 1);
    l.deserialize(level, *mBoard, mPlayers);
    if(mPlayers[1])
        mPlayers[1]->setSkinID(1);
}

void Game::addObject(GameObject *object)
{
    mBoard->addObject(object);
    if(object->getType() == GameObject::PLAYER)
        mPlayers.push_back(dynamic_cast<Player*>(object));
}

Board *Game::getBoard()
{
    return mBoard;
}

void Game::move()
{
    if (mPlayers[0] && mPlayers[0]->getLives() < 1 && mOnGameOver)
    {
        LOG_MIL("Plyer 2 won");
        mOnGameOver();
    }
    else if(mPlayers[1] && mPlayers[1]->getLives() < 1 && mOnGameOver)
    {
        LOG_MIL("Plyer 1 won");
        mOnGameOver();
    }
    mBoard->move();

    for(int i = 0 ; i < mEnemies.size(); i++)
    {
        int currentPlayerID = mEnemies[i]->getPlayerID();
        bool status;
        if(mPlayers[currentPlayerID]->getSpeed() == 0)
            status = false;
        else
            status = true;
        mEnemies[i]->undateState(status);
    }
}


void Game::move (int playerID, GameObject::Direction directio)
{
    if(playerID >=0 && playerID < mPlayers.size())
    {
        mPlayers[playerID]->setDirection(directio);
        //mPlayers[playerID]->setEnemy(true);
    }
}
    
void Game::stop (int playerID)
{
    if(playerID >=0 && playerID < mPlayers.size())
    {
        mPlayers[playerID]->stopObject();
    }
}
    
void Game::placeBomb (int playerID)
{
    if(playerID >=0 && playerID < mPlayers.size())
    {
        //check if bomb can be placed in the board at the wanted place, no collisions
        std::vector<GameObject*> objectsInCell;
        if(mPlayers[playerID]->getDirection() == GameObject::UP && mPlayers[playerID]->getSpeed() > 0)
        {
            objectsInCell = mBoard->getAllCollisionsWithCell(mPlayers[playerID]->getRow()+1, mPlayers[playerID]->getColumn());
        }
        else if(mPlayers[playerID]->getDirection() == GameObject::LEFT && mPlayers[playerID]->getSpeed() > 0)
        {
            objectsInCell = mBoard->getAllCollisionsWithCell(mPlayers[playerID]->getRow(), mPlayers[playerID]->getColumn()+1);
        }
        else
            objectsInCell = mBoard->getAllCollisionsWithCell(mPlayers[playerID]->getRow(), mPlayers[playerID]->getColumn());
        if(objectsInCell.size() == 0 || (objectsInCell.size() == 1 && objectsInCell[0] == mPlayers[playerID]))
        {
            Bomb *bomb = mPlayers[playerID]->placingBomb(mBoard);
            //we can only place bomb if there is nothing for it to colide with
            if (bomb)
            {
                addObject(bomb);
            }
        }
    }
    else
        LOG_ERROR("player index invalid %d", playerID);
}

void Game::addEnemy(IEnemy* enemy)
{
    mEnemies.push_back(enemy);
}
