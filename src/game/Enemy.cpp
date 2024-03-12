#include "Enemy.h"
#include "GameObject.h"


Enemy::Enemy(IPlayerControl* control, int playerID)
{
    mControl = control;
    mID = playerID;
}

int Enemy::getPlayerID() const
{
    return mID;
}


void Enemy::undateState(bool ismoving)
{
    mIsMoving = ismoving;
    if(!mIsMoving)
    {
        GameObject::Direction newDirection = (GameObject::Direction)(rand()%((int)(GameObject::STATIONARY)));
        mControl->move(mID, newDirection);
    }
}
