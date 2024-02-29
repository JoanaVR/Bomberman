#include <sstream>
#include <iostream>
#include <SDL3/SDL.h>
#include "game/Board.h"
#include <traits.h>
#include <thread>
#include <chrono>

using namespace std;

Board::Board(int row, int column)
{
    mRows = row;
    mColumns = column;
    mWidth = mColumns * GameObject::cellSize;
    mHight = mRows * GameObject::cellSize;
}

Board &Board::operator=(const Board &b)
{
    mRows = b.mRows;
    mColumns = b.mColumns;
    mWidth = b.mWidth;
    mHight = b.mHight;
    mGameObjects = b.mGameObjects;
    const_cast<Board &>(b).mGameObjects.clear();
    return *this;
}

int Board::getRows() const
{
    return mRows;
}

int Board::getColumns() const
{
    return mColumns;
}

int Board::getWidth() const
{
    return mWidth;
}

int Board::getHight() const
{
    return mHight;
}

int Board::getBoardSize() const
{
    return mRows * mColumns;
}

void Board::addObject(GameObject *object)
{
    mGameObjects.push_back(object);
}

int Board::getGameObjectsSize() const
{
    return mGameObjects.size();
}

const GameObject *Board::getObject(int index) const
{
    return mGameObjects[index];
}

Player *Board::getPlayer()
{
    for (int i = 0; i < mGameObjects.size(); i++)
    {
        if (mGameObjects[i]->getType() == GameObject::PLAYER)
        {
            return dynamic_cast<Player *>(mGameObjects[i]);
        }
    }
    return nullptr;
}

std::vector<std::pair<GameObject *, GameObject *>> Board::findCollisions()
{
    std::vector<std::pair<GameObject *, GameObject *>> result;
    for (int i = 0; i < mGameObjects.size(); i++)
    {
        for (int j = i + 1; j < mGameObjects.size(); j++)
        {
            GameObject::Direction currentDirectionFierstObject =  mGameObjects[i]->getDirection();
            GameObject::Direction currentDirectionSecondObject =  mGameObjects[j]->getDirection();
            if (mGameObjects[i]->getSpeed() == 0 && mGameObjects[j]->getSpeed() == 0)
            {
                continue;
            }
            rava::traits::Rect rectangle1;
            mGameObjects[i]->getNextMoveRectangle(rectangle1);
            rava::traits::Rect rectangle2;
            mGameObjects[j]->getNextMoveRectangle(rectangle2);
            //obly report collisions if there hasnt been a change in direction, if there has been then the objects will not collide.
            //if((currentDirectionFierstObject ==  mGameObjects[i]->getDirection()) && (currentDirectionSecondObject ==  mGameObjects[j]->getDirection()))
            {
                if (rectangle1.intersect(rectangle2))
                {
                    result.push_back({mGameObjects[i], mGameObjects[j]});
                }
            }
        }
    }
    return result;
}

void Board::stopOutOfBoardObjects()
{
    for (size_t i = 0; i < mGameObjects.size(); i++)
    {
        GameObject::Direction currentDirection =  mGameObjects[i]->getDirection();
        if (mGameObjects[i]->getSpeed() == 0)
        {
            continue;
        }
        auto x = mGameObjects[i]->getmX();
        auto y = mGameObjects[i]->getmY();

        switch (mGameObjects[i]->getDirection())
        {
        case GameObject::RIGHT:
            x += mGameObjects[i]->getSpeed();
            break;
        case GameObject::LEFT:
            x -= mGameObjects[i]->getSpeed();
            break;
        case GameObject::DOWN:
            y += mGameObjects[i]->getSpeed();
            break;
        case GameObject::UP:
            y -= mGameObjects[i]->getSpeed();
            break;
        }
        
        if (x < 0 || x > ((mColumns - 1) * GameObject::cellSize))
        {
            mGameObjects[i]->forceStopObject();
        }
        else if (y < 0 || y > ((mRows - 1) * GameObject::cellSize))
        {
            mGameObjects[i]->forceStopObject();
        }
    }
}

void Board::move()
{
    stopOutOfBoardObjects();

    std::vector<std::pair<GameObject *, GameObject *>> collisions = findCollisions();

    for (size_t i = 0; i < collisions.size(); i++)
    {
        if (collisions[i].first->canPassThrough() == false || collisions[i].second->canPassThrough() == false)
        {
            collisions[i].first->forceStopObject();
            collisions[i].second->forceStopObject();
        }
    }

    for (size_t i = 0; i < mGameObjects.size(); i++)
    {
        mGameObjects[i]->move();
    }
}

void Board::removeObject(int row, int column)
{
    for (int i = 0; i < mGameObjects.size(); i++)
    {
        if (mGameObjects[i]->getRow() == row && mGameObjects[i]->getColumn() == column)
        {
            delete mGameObjects[i];
            mGameObjects.erase(mGameObjects.begin() + i);
            break;
        }
    }
}

void Board::reducePlayerLife()
{
    if(getPlayer()->getLives() == 1)
    {
       // remove player and gameOver
    }
    else
    {
        getPlayer()->reduceLives();
    }

}


void Board::explode(int bombRow, int bombColumn, int explosionRadius)
{
    if(mGameObjects.size()< explosionRadius)
    {
        explosionRadius = mGameObjects.size();
    }
    // find the first object to the right of the bomb
    for (int i = 0; i < explosionRadius; i++)
    {
        if (mGameObjects[i]->getRow() == bombRow && mGameObjects[i]->getColumn() > bombColumn)
        {
            if (mGameObjects[i]->getType() == GameObject::EMPTY)
                continue;
            else if (mGameObjects[i]->getType() == GameObject::BLOCK)
            {
                removeObject(mGameObjects[i]->getRow(), mGameObjects[i]->getColumn());
                break;
            }
            else if (mGameObjects[i]->getType() == GameObject::PLAYER)
            {
                reducePlayerLife();
                break;
            }
            else
                break;
        }
    }
    // find the first object to the left of the bomb
    for (int i = 0; i < explosionRadius; i++)
    {
        if (mGameObjects[i]->getRow() == bombRow && mGameObjects[i]->getColumn() < bombColumn)
        {
            if (mGameObjects[i]->getType() == GameObject::EMPTY)
                continue;
            else if (mGameObjects[i]->getType() == GameObject::BLOCK)
            {
                removeObject(mGameObjects[i]->getRow(), mGameObjects[i]->getColumn());
                break;
            }
            else if (mGameObjects[i]->getType() == GameObject::PLAYER)
            {
                reducePlayerLife();
                break;
            }
            else
                break;
        }
    }
    // find the first object on top of the bomb
    for (int i = 0; i < explosionRadius; i++)
    {
        if (mGameObjects[i]->getColumn() == bombColumn && mGameObjects[i]->getRow() < bombRow)
        {
            if (mGameObjects[i]->getType() == GameObject::EMPTY)
                continue;
            else if (mGameObjects[i]->getType() == GameObject::BLOCK)
            {
                removeObject(mGameObjects[i]->getRow(), mGameObjects[i]->getColumn());
                break;
            }
            else if (mGameObjects[i]->getType() == GameObject::PLAYER)
            {
                reducePlayerLife();
                break;
            }
            else
                break;
        }
    }
    // find the first object under the bomb
    for (int i = 0; i < explosionRadius; i++)
    {
        if (mGameObjects[i]->getColumn() == bombColumn && mGameObjects[i]->getRow() > bombRow)
        {
            if (mGameObjects[i]->getType() == GameObject::EMPTY)
                continue;
            else if (mGameObjects[i]->getType() == GameObject::BLOCK)
            {
                removeObject(mGameObjects[i]->getRow(), mGameObjects[i]->getColumn());
                break;
            }
            else if (mGameObjects[i]->getType() == GameObject::PLAYER)
            {
                reducePlayerLife();
                break;
            }
            else
                break;
        }
    }
    removeObject(bombRow, bombColumn);
}

void Board::placeBomb(int row, int column)
{
    Bomb *bomb = new Bomb(row, column, this);
    addObject(bomb);
}
