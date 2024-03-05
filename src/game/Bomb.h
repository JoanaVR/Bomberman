#pragma once
#include "GameObject.h"
#include "BombExplosionNotification.h"

class Bomb: public GameObject
{
    public:
    Bomb(int row, int column, BombExplosionNotification* n, int explosionRadius);
    GameObject::ObjectType getType() const; 
    virtual void move() override;
    int getExplosionRadius() const;

    private:
    int timer;
    BombExplosionNotification* mNotifier;
    int mExplosionRadius;
};