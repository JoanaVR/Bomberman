#include "Bomb.h"

using namespace std;

Bomb::Bomb(int row, int column, BombExplosionNotification* n, int explosionRadius) : GameObject(row, column)
{
    mCanPassThrough = false;
    mNotifier = n;
    timer = 0;
    mExplosionRadius = explosionRadius;
}


GameObject::ObjectType Bomb::getType() const
{
    return BOMB;
}

int Bomb::getExplosionRadius() const
{
    return mExplosionRadius;
}

void Bomb::move()
{
    timer++;
    if(timer > 50)
    {
        mCanPassThrough = false;
    }
    if (timer > 200)
    {
        mNotifier->explode(this);

    }
    GameObject::move();
}


