#include "Explosion.h"

using namespace std;

Explosion::Explosion(int row, int column, Direction direction, bool isEnd) : GameObject(row, column)
{
    mCanPassThrough = true;
    mExplosionDirection = direction;
    mIsEndExplosion = isEnd;
    timer = 0;
}


GameObject::ObjectType Explosion::getType() const
{
    return EXPLOSION;
}

void Explosion::move()
{ 
    timer++;
    if(timer > 50)
    {
        setToRemove();
    }
    GameObject::move();
}

