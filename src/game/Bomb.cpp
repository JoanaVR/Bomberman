#include "Bomb.h"

using namespace std;

Bomb::Bomb(int row, int column, BombExplosionNotification* n, int explosionRadius) : GameObject(row, column)
{
    mCanPassThrough = false;
    mNotifier = n;
    mTimer = 0;
    mExplosionRadius = explosionRadius;
    mExplosionStartedTimer = -1;
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
    mTimer++;
    if(mExplosionStartedTimer != -1)
        mExplosionStartedTimer ++;
    if(mTimer > 50)
    {
        mCanPassThrough = false;
    }
    if (mTimer > 200 || mExplosionStartedTimer > 10)
    {
        mNotifier->explode(this);

    }
    GameObject::move();
}

void Bomb::collision(GameObject *object)
{
    if (object->getType() == GameObject::EXPLOSION)
    {
        //if timer hasnt statred then start it 
        if(mExplosionStartedTimer == -1)
            mExplosionStartedTimer = 0;
    }
    else
    {
        forceStopObject();
    }
}

