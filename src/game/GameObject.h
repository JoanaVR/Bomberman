#pragma once

#include <traits.h>
#include "queue"

class Board;
class GameObject 
{
    public:

    enum ObjectType 
    {
        PLAYER,
        BLOCK,
        UNBREAKABLE_BLOCK,
        POWERUP,
        EMPTY,
        BOMB
    };

    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    GameObject(int row, int column);
    virtual ObjectType getType() const = 0; //this will be overwritten by every object that inherits the game object
    virtual void setSpeed(int speed);
    virtual void setDirection(Direction direction);
    virtual void move();
    int getRow() const;
    int getColumn() const;
    void getNextMoveRectangle(rava::traits::Rect& r, bool shrink = true) const;
    void getRectangle(rava::traits::Rect& r) const;
    void stopObject();
    void forceStopObject();
    bool isNextStepDifferentCell();
    int getSpeed();
    Direction getDirection();
    Direction getNextDirection();
    bool canPassThrough();
    int getmX();
    int getmY();
    void alignObjectToNearestCell();
    void alignMovingObjectToCell(Direction direction);

    static int cellSize; 
    static void setCellSize(int size);
    static void setDefaulfSpeed(int speed);

    protected:
    int mSpeed;
    int mRow;
    int mColumn;
    int mX;
    int mY;
    Direction mDirection;
    bool mCanPassThrough;
    Direction mNextDirection;
    bool mIsMoving;
    static int mDefaultSpeed;

};
