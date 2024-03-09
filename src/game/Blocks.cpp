#include "game/Blocks.h"

using namespace std;

Block::Block(bool isBreckable, int row, int column, PowerUp::PowerUpType powerUpType, BlockToPowerUpNotification* notifier) : GameObject(row, column)
{
    mIsBreackable = isBreckable;
    mSpeed = 0;
    mCanPassThrough = false;
    mPowerupType = powerUpType;
    mNotifier = notifier;
}


GameObject::ObjectType Block::getType() const
{
    if(mIsBreackable)
        return BLOCK;
    else
        return UNBREAKABLE_BLOCK;
}

void Block::collision(GameObject* object)
{
    if(object->getType() == GameObject::EXPLOSION && mIsBreackable)
    {
        mNotifier->createPowerUp(this, dynamic_cast<Explosion*>(object));
        setToRemove();
    }
    else
    {
        GameObject::collision(object);
    }
}

PowerUp::PowerUpType Block::getPowerUpType() const
{
        return mPowerupType;
}

