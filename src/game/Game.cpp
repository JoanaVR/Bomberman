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

void Game::keyboardEvent(int key, int scancode, int action, int modifiers)
{
    static std::map<int, bool> currentKeysPlayer1 = {{K_UP, false},
                                                     {K_DOWN, false},
                                                     {K_RIGHT, false},
                                                     {K_LEFT, false}};

    static std::map<int, bool> currentKeysPlayer2 = {{K_w, false},
                                                     {K_s, false},
                                                     {K_d, false},
                                                     {K_a, false}};

    if (action == PRESSED)
    {
        LOG_MIL("keyboardEvent pressed, key: %d", key);
        switch (key)
        {
        case K_UP:
        {
            currentKeysPlayer1[key] = true;

            mPlayers[0]->setDirection(GameObject::UP);
        }
        break;
        case K_DOWN:
        {
            currentKeysPlayer1[key] = true;
            mPlayers[0]->setDirection(GameObject::DOWN);
        }
        break;
        case K_RIGHT:
        {
            currentKeysPlayer1[key] = true;
            mPlayers[0]->setDirection(GameObject::RIGHT);
        }
        break;
        case K_LEFT:
        {
            currentKeysPlayer1[key] = true;
            mPlayers[0]->setDirection(GameObject::LEFT);
        }
        break;
        case K_ENTER:
        {
            placeBomb(0);
        }
        break;
        case K_w:
        {
            currentKeysPlayer2[key] = true;
            mPlayers[1]->setDirection(GameObject::UP);
        }
        break;
        case K_s:
        {
            currentKeysPlayer2[key] = true;
            mPlayers[1]->setDirection(GameObject::DOWN);
        }
        break;
        case K_d:
        {
            currentKeysPlayer2[key] = true;
            mPlayers[1]->setDirection(GameObject::RIGHT);
        }
        break;
        case K_a:
        {
            currentKeysPlayer2[key] = true;
            mPlayers[1]->setDirection(GameObject::LEFT);
        }
        break;
        case K_SPACE:
        {
            placeBomb(1);
        }
        break;
        default:
            break;
        }
    }
    else if (action == RELEASED)
    {
        switch (key)
        {
        case K_UP:
        {
            currentKeysPlayer1[key] = false;
        }
        break;
        case K_DOWN:
        {
            currentKeysPlayer1[key] = false;
        }
        break;
        case K_RIGHT:
        {
            currentKeysPlayer1[key] = false;
        }
        break;
        case K_LEFT:
        {
            currentKeysPlayer1[key] = false;
        }
        break;
        case K_w:
        {
            currentKeysPlayer2[key] = false;
        }
        break;
        case K_s:
        {
            currentKeysPlayer2[key] = false;
        }
        break;
        case K_d:
        {
            currentKeysPlayer2[key] = false;
        }
        break;
        case K_a:
        {
            currentKeysPlayer2[key] = false;
        }
        break;
        }
        LOG_MIL("keyboardEvent RELESED, key: %d", key);
        bool havePressedDirectionPlayer1 = false;
        for (auto &i : currentKeysPlayer1)
        {
            havePressedDirectionPlayer1 |= i.second;
        }
        if (!havePressedDirectionPlayer1)
            mPlayers[0]->stopObject();

        bool havePressedDirectionPlayer2 = false;
        for (auto &i : currentKeysPlayer2)
        {
            havePressedDirectionPlayer2 |= i.second;
        }
        if (!havePressedDirectionPlayer2)
            mPlayers[1]->stopObject();
    }
}


void Game::move (int playerID, GameObject::Direction directio)
{
    if(playerID >=0 && playerID < mPlayers.size())
    {
        mPlayers[playerID]->setDirection(directio);
        mPlayers[playerID]->setEnemy(true);
    }
}
    
void Game::stop (int playerID)
{
    if(playerID >=0 && playerID < mPlayers.size())
        mPlayers[playerID]->stopObject();
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
