#include "GameObject.h"
#include <iostream>
#include <Logging.h>

using namespace std;

int GameObject::cellSize = 100;
int GameObject::mDefaultSpeed = 5;

GameObject::GameObject(int row, int column)
{
    mRow = row;
    mColumn = column;
    mX = mColumn * cellSize;
    mY = mRow * cellSize;
    mIsMoving = false;
    mSpeed = 0;
}

void GameObject::setCellSize(int size)
{
    cellSize = size;
}

void GameObject::setDefaulfSpeed(int speed)
{
    mDefaultSpeed = speed;
}

int GameObject::getRow() const
{
    return mY / cellSize;
}

int GameObject::getColumn() const
{
    return mX / cellSize;
}

int GameObject::getSpeed()
{
    return mSpeed;
}

GameObject::Direction GameObject::getDirection()
{
    return mDirection;
}
GameObject::Direction GameObject::getNextDirection()
{
    return mNextDirection;
}

bool GameObject::canPassThrough()
{
    return mCanPassThrough;
}

int GameObject::getmX()
{
    return mX;
}

int GameObject::getmY()
{
    return mY;
}

bool GameObject::isNextStepDifferentCell()
{
    rava::traits::Rect futureRect;
    getNextMoveRectangle(futureRect, false);

    // check if next step is out of board
    if (futureRect.x1() < 0 || futureRect.y1() < 0)
        return true;

    if ((mX / cellSize == futureRect.x1() / cellSize) && (mY / cellSize == futureRect.y1() / cellSize))
    {
        LOG_MIL("not next cell x: %d, y: %d", mX, mY);
        return false;
    }
    LOG_MIL("next cell x: %d, y: %d", mX, mY);
    return true;
}

void GameObject::move()
{
    if (mSpeed > 0)
    {
        bool nextStepDifferentCell = isNextStepDifferentCell();
        auto doStep = [this]()
        {
            switch (mDirection)
            {
            case UP:
                if (mY > 0)
                {
                    mY -= mSpeed;
                    mRow = mY / cellSize;
                }
                break;
            case DOWN:
                mY += mSpeed;
                mRow = mY / cellSize;
                break;
            case LEFT:
                if (mX > 0)
                {
                    mX -= mSpeed;
                    mColumn = mX / cellSize;
                }
                break;
            case RIGHT:
                mX += mSpeed;
                mColumn = mX / cellSize;
                break;
            }
        };
        // if we are in a cell then we can change direction
        if (nextStepDifferentCell)
        {
            // LOG_MIL("next cell different x: %d, y: %d", mX, mY);
            bool flag = (mDirection != mNextDirection);
            if (flag)
            {
                alignMovingObjectToCell(mDirection);
                // LOG_MIL("after slighnment x: %d, y: %d", mX, mY);
                mDirection = mNextDirection;
            }
            if (mIsMoving == false)
            {
                LOG_MIL("force stop");
                forceStopObject();
            }
            else if (!flag)
            {
                doStep();
            }
        }
        else
        {
            doStep();
        }
    }
}

void GameObject::setSpeed(int speed)
{
    mSpeed = speed;
}

void GameObject::alignObjectToNearestCell()
{
    auto x = (mX / cellSize) * cellSize + cellSize / 2;
    auto y = (mY / cellSize) * cellSize + cellSize / 2;
    if (mX < x)
        mX = (mX / cellSize) * cellSize;
    else if (mX > x)
        mX = (mX / cellSize) * cellSize + cellSize;
    if (mY < y)
        mY = (mY / cellSize) * cellSize;
    else if (mY > y)
        mY = (mY / cellSize) * cellSize + cellSize;
}

void GameObject::alignMovingObjectToCell(Direction direction)
{
    switch (direction)
    {
    case UP:
        mRow = (mY / cellSize);
        mY = mRow * cellSize;
        break;
    case DOWN:
        mRow = (mY / cellSize) + 1;
        mY = mRow * cellSize;
        break;
    case LEFT:
        mColumn = (mX / cellSize);
        mX = mColumn * cellSize;
        break;
    case RIGHT:
        mColumn = (mX / cellSize) + 1;
        mX = mColumn * cellSize;
        break;
    }
}

void GameObject::forceStopObject()
{
    if (mDirection == mNextDirection || !isNextStepDifferentCell())
    {
        mSpeed = 0;
        mIsMoving = false;
        alignObjectToNearestCell();
    }
}

void GameObject::stopObject()
{
    LOG_MIL("stop object");
    mIsMoving = false;

    /*
    if (mSpeed == 0)
        return;

    std::cout << "this is mx and my:" << mX << ", "<< mY<< std::endl;

    auto x = (mX/cellSize)*cellSize + cellSize/2;
    auto y = (mY/cellSize)*cellSize + cellSize/2;
    if(mX < x)
        mX = (mX/cellSize)*cellSize;
    else if (mX > x)
        mX = (mX/cellSize)*cellSize + cellSize;
    if(mY < y)
        mY = (mY/cellSize)*cellSize;
    else if (mY > y)
        mY = (mY/cellSize)*cellSize + cellSize;
    */
}

void GameObject::setDirection(Direction direction)
{
    mNextDirection = direction;
    if (mIsMoving == false && mSpeed == 0)
    {
        mDirection = mNextDirection;
    }
    mIsMoving = true;
    mSpeed = mDefaultSpeed;
}

void GameObject::getNextMoveRectangle(rava::traits::Rect &r, bool shrink) const
{
    // r = {mX, mY, mX + cellSize , mY + cellSize };
    // return;

    r.setX1(mX);
    r.setX2(mX + cellSize);
    r.setY1(mY);
    r.setY2(mY + cellSize);

    if (shrink)
    {
        r.shrink(1);
    }
    if (mSpeed != 0)
    {
        switch (mDirection)
        {
        case RIGHT:
            r.translate(mSpeed, 0);
            break;
        case LEFT:
            r.translate(-mSpeed, 0);
            break;
        case DOWN:
            r.translate(0, mSpeed);
            break;
        case UP:
            r.translate(0, -mSpeed);
            break;
        }
    }
}

void GameObject::getRectangle(rava::traits::Rect &r) const
{
    r = {mX, mY, mX + cellSize, mY + cellSize};
}
