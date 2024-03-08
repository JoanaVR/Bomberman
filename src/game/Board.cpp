#include <sstream>
#include <iostream>
#include <SDL3/SDL.h>
#include "game/Board.h"
#include <traits.h>
#include <thread>
#include <chrono>
#include "Explosion.h"

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
std::vector<GameObject*> Board::getAllCollisionsWithCell(int row, int column)
{
    std::vector<GameObject*> result = {}; 
    
    rava::traits::Rect cellRect;
    cellRect.setX1(column*GameObject::cellSize);
    cellRect.setX2(column*GameObject::cellSize + GameObject::cellSize);
    cellRect.setY1(row*GameObject::cellSize);
    cellRect.setY2(row*GameObject::cellSize + GameObject::cellSize);
    for (int i = 0; i < mGameObjects.size(); i++)
    {
        rava::traits::Rect objectRect;
        mGameObjects[i]->getNextMoveRectangle(objectRect);
        if (objectRect.intersect(cellRect))
        {
            result.push_back(mGameObjects[i]);
        }
    }
    return result;
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
            GameObject::Direction currentDirectionFierstObject = mGameObjects[i]->getDirection();
            GameObject::Direction currentDirectionSecondObject = mGameObjects[j]->getDirection();
            if (mGameObjects[i]->getSpeed() == 0 && mGameObjects[j]->getSpeed() == 0 &&
                mGameObjects[i]->getType() != GameObject::EXPLOSION && mGameObjects[j]->getType() != GameObject::EXPLOSION)
            {
                continue;
            }
            rava::traits::Rect rectangle1;
            mGameObjects[i]->getNextMoveRectangle(rectangle1);
            rava::traits::Rect rectangle2;
            mGameObjects[j]->getNextMoveRectangle(rectangle2);
            if (rectangle1.intersect(rectangle2))
            {
                result.push_back({mGameObjects[i], mGameObjects[j]});
            }
        }
    }
    return result;
}

void Board::stopOutOfBoardObjects()
{
    for (size_t i = 0; i < mGameObjects.size(); i++)
    {
        GameObject::Direction currentDirection = mGameObjects[i]->getDirection();
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
        collisions[i].first->collision(collisions[i].second);
        collisions[i].second->collision(collisions[i].first);
    }

    for (size_t i = 0; i < mGameObjects.size(); i++)
    {
        mGameObjects[i]->move();
    }
    // check each object to see if they need to be removed
    auto it = std::remove_if(mGameObjects.begin(), mGameObjects.end(), [](GameObject *object)
                             { return object->shouldRemove(); });
    mGameObjects.erase(it, mGameObjects.end());
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

void Board::removeObject(GameObject* object)
{
    auto it = std::find(mGameObjects.begin(), mGameObjects.end(), object); 
    mGameObjects.erase(it);
    delete object;
}

bool Board::isObjectInBombRadius(int bombRow, int bombColumn, int explosionRadius, int objectRow, int objectColumn)
{
    if (objectColumn == bombColumn && objectRow <= (bombRow + explosionRadius) && objectRow >= (bombRow - explosionRadius))
    {
        return true;
    }
    if (objectRow == bombRow && objectColumn <= (bombColumn + explosionRadius) && objectColumn >= (bombColumn - explosionRadius))
    {
        return true;
    }
    return false;
}

GameObject::ObjectType Board::getObjectType(int row, int column)
{
    for (int i = 0; i < mGameObjects.size(); i++)
    {
        if (mGameObjects[i]->getRow() == row && mGameObjects[i]->getColumn() == column)
        {
            return mGameObjects[i]->getType();
        }
    }
    return GameObject::EMPTY;
}

void Board::explode(Bomb* bomb)
{
    // place explosions where the bomb
    auto bombRow = bomb->getRow();
    auto bombColumn = bomb->getColumn();
    auto explosionRadius = bomb->getExplosionRadius();
    removeObject(bomb);
    Explosion *explosion = new Explosion(bombRow, bombColumn, GameObject::STATIONARY, false);
    addObject(explosion);

    // Explosion *explosion =  nullptr;
    //  find first object under bomb
    int finalCellToExplode = 0;
    if (bombRow + explosionRadius > mRows-1)
        finalCellToExplode = mRows-1;
    else
        finalCellToExplode = bombRow + explosionRadius;
    for (int i = bombRow + 1; i <= finalCellToExplode; i++)
    {
        GameObject::ObjectType currentObjectType = getObjectType(i, bombColumn);
        if (currentObjectType == GameObject::UNBREAKABLE_BLOCK)
            break;
        // check if last explosion to change type. -1 because timer starts from 0
        if (i == finalCellToExplode - 1)
        {
            explosion = new Explosion(i, bombColumn, GameObject::STATIONARY, true);
        }
        else
        {
            explosion = new Explosion(i, bombColumn, GameObject::STATIONARY, false);
        }
        addObject(explosion);
        if (currentObjectType == GameObject::BLOCK)
            break;
    }

    // find first object on top of bomb
    if (bombRow - explosionRadius < 0)
        finalCellToExplode = 0;
    else
        finalCellToExplode = bombRow - explosionRadius;
    for (int i = bombRow - 1; i >= finalCellToExplode; i--)
    {
        GameObject::ObjectType currentObjectType = getObjectType(i, bombColumn);
        if (currentObjectType == GameObject::UNBREAKABLE_BLOCK)
            break;
        if (i == finalCellToExplode)
        {
            explosion = new Explosion(i, bombColumn, GameObject::STATIONARY, true);
        }
        else
        {
            explosion = new Explosion(i, bombColumn, GameObject::STATIONARY, false);
        }
        addObject(explosion);
        if (currentObjectType == GameObject::BLOCK)
            break;
    }

    // find first object to the right of bomb
    if (bombColumn + explosionRadius > mColumns-1)
        finalCellToExplode = mColumns-1;
    else
        finalCellToExplode = bombColumn + explosionRadius;
    for (int i = bombColumn + 1; i <= finalCellToExplode; i++)
    {
        GameObject::ObjectType currentObjectType = getObjectType(bombRow, i);
        if (currentObjectType == GameObject::UNBREAKABLE_BLOCK)
            break;
        if (i == finalCellToExplode - 1)
        {
            explosion = new Explosion(bombRow, i, GameObject::STATIONARY, true);
        }
        else
        {
            explosion = new Explosion(bombRow, i, GameObject::STATIONARY, false);
        }
        addObject(explosion);
        if (currentObjectType == GameObject::BLOCK)
            break;
    }

    // find first object to the left of bomb
    if (bombColumn - explosionRadius < 0)
        finalCellToExplode = 0;
    else
        finalCellToExplode = bombColumn - explosionRadius;
    for (int i = bombColumn - 1; i >= finalCellToExplode; i--)
    {
        GameObject::ObjectType currentObjectType = getObjectType(bombRow, i);
        if (currentObjectType == GameObject::UNBREAKABLE_BLOCK)
            break;
        if (i == finalCellToExplode)
        {
            explosion = new Explosion(bombRow, i, GameObject::STATIONARY, true);
        }
        else
        {
            explosion = new Explosion(bombRow, i, GameObject::STATIONARY, false);
        }
        addObject(explosion);
        if (currentObjectType == GameObject::BLOCK)
            break;
    }
}

