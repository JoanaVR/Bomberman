#include "Player.h"
#include "Bomb.h"

using namespace std;

Player::Player(int row, int column) : GameObject(row, column)
{
    mCanPassThrough = true;
    mLives = 3;
    mBomb = nullptr;
    mTimer = 0;
}

Player::~Player()
{
    

}

void Player::placingBomb(GameObject* bomb)
{
    mBomb = bomb;
}

GameObject::ObjectType Player::getType() const
{
    return PLAYER;
}

int Player::getLives()
{
    return mLives;
}

void Player::reduceLives()
{
    mLives -= 1;
}

Player::State Player::getState() const
{
    return mState;
}


bool Player::isMyBomb(GameObject* bomb)
{
    if(mBomb == bomb)
        return true;
    return false;
}


void Player::collision(GameObject* object)
{
    if(object->getType() == GameObject::EXPLOSION)
    {
        mState = DYEING;
        reduceLives();
        forceStopObject();
        mTimer = 100;
    }
    else if(object->getType() == GameObject::BOMB)
    {
        if(!isMyBomb(object))
            forceStopObject();
    }
    else
    {
        forceStopObject();
    }
}

void Player::move()
{
    if(mTimer != 0)
    {
        mTimer -= 1;
    }
    else
    {
        mState = NORMAL;
        GameObject::move();
        //check if player is still in same cell as placed bomb
        if(mBomb != nullptr)
        {
            //checkif i have an intersection my bomb
            rava::traits::Rect bombRectangle;
            mBomb->getRectangle(bombRectangle);
            bombRectangle.shrink(1);
            rava::traits::Rect playerRectangle;
            getRectangle(playerRectangle);
            playerRectangle.shrink(1);

            if(!bombRectangle.intersect(playerRectangle))
                mBomb = nullptr;
        }
    }
}

void Player::accept(IGameObjectVisitor* visitor) const
{
    visitor->visit(this);
}

