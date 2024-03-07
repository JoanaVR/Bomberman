#include "Game.h"
#include "Level.h"
#include "Board.h"

#include <Logging.h>

#include <map>

Game::Game(const std::string &level, std::function<void ()> onGameOver)
{
    mOnGameOver = onGameOver;
    Level l;
    mBoard = new Board(1, 1);
    l.deserialize(level, *mBoard, mPlayers);
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
    if(mPlayers[0] && mPlayers[0]->getLives() < 1 && mOnGameOver)
    {
        mOnGameOver();
    }
    mBoard->move();
}

void Game::keyboardEvent(int key, int scancode, int action, int modifiers)
    {
        static std::map<int, bool> currentKeys = {{K_UP, false}, 
                                                  {K_DOWN, false}, 
                                                  {K_RIGHT, false}, 
                                                  {K_LEFT, false} };


        if (action == PRESSED)
        {
            LOG_MIL("keyboardEvent pressed, key: %d", key);    
            currentKeys[key] = true;
            switch (key)
            {
            case K_UP:
            {
                mPlayers[0]->setDirection(GameObject::UP);
            }
            break;
            case K_DOWN:
            {
                mPlayers[0]->setDirection(GameObject::DOWN);
            }
            break;
            case K_RIGHT:
            {
                mPlayers[0]->setDirection(GameObject::RIGHT);
            }
            break;
            case K_LEFT:
            {
                mPlayers[0]->setDirection(GameObject::LEFT);
            }
            break;
            case K_ENTER:
            {
                Bomb *bomb = mPlayers[0]->placingBomb(mBoard);
                if(bomb)
                    addObject(bomb);
            }
            break;
            case K_w:
            {
                mPlayers[1]->setDirection(GameObject::UP);
            }
            break;
            case K_s:
            {
                mPlayers[1]->setDirection(GameObject::DOWN);
            }
            break;
            case K_d:
            {
                mPlayers[1]->setDirection(GameObject::RIGHT);
            }
            break;
            case K_a:
            {
                mPlayers[1]->setDirection(GameObject::LEFT);
            }
            break;
            case K_SPACE:
            {
                Bomb *bomb = mPlayers[1]->placingBomb(mBoard);
                if(bomb)
                    addObject(bomb);
            }
            break;
            default:
            break;
            }
        }
        else if (action == RELEASED)
        {
            currentKeys[key] = false;
            LOG_MIL("keyboardEvent RELESED, key: %d", key);
            bool havePressedDirection = false;    
            for(auto &i : currentKeys )
            {
                havePressedDirection |= i.second;
            }
            if(!havePressedDirection)
                mPlayers[0]->stopObject();
        }
    }