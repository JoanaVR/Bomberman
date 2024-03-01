#include "Bomb.h"

using namespace std;

Bomb::Bomb(int row, int column, BombExplosionNotification* n) : GameObject(row, column)
{
    mCanPassThrough = true;
    mNotifier = n;
}


GameObject::ObjectType Bomb::getType() const
{
    return BOMB;
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
        mNotifier->explode(mRow, mColumn, 2);

    }
    GameObject::move();
}

