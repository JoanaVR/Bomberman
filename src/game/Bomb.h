#pragma once
#include "GameObject.h"
#include "BombExplosionNotification.h"

class Bomb: public GameObject
{
    public:
    Bomb(int row, int column, BombExplosionNotification* n);
    GameObject::ObjectType getType() const; 
    virtual void move() override;

    private:
    int timer;
    BombExplosionNotification* mNotifier;
};