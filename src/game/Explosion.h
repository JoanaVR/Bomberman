#pragma once
#include "GameObject.h"

class Explosion: public GameObject
{
    public:
    Explosion(int row, int column, Direction direction, bool isEnd);
    GameObject::ObjectType getType() const; 
    virtual void move() override;

    private:
    int explosionRow;
    int explosionColumn;
    GameObject::Direction mExplosionDirection;
    bool mIsEndExplosion;
    int timer;
};