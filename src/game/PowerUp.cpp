#include "PowerUp.h"

PowerUp::PowerUp(int row, int column, PowerUpType type) : GameObject(row, column)
{
    mPowerUpType = type;
    mCanPassThrough = true;
    mExplosion = nullptr;
}

GameObject::ObjectType PowerUp::getType() const
{
    return GameObject::POWERUP;
}

void PowerUp::collision(GameObject *object)
{
    if (object->getType() == GameObject::PLAYER)
    {
        //collected by player
        setToRemove();
    }
    else if (object->getType() == GameObject::EXPLOSION)
    {
        //unless ecplsion that removed block to uncover power up, it removes power up
        if(object != mExplosion)
            setToRemove();
    }
    if (object->getType() == GameObject::PLAYER)
    {
        //collected ny player
        setToRemove();
    }
}
void PowerUp::setExplosion(Explosion* explosion)
{
    mExplosion = explosion;
}
