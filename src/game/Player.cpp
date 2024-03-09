#include "Player.h"
#include "Bomb.h"
#include "BombExplosionNotification.h"

using namespace std;

Player::Player(int row, int column) : GameObject(row, column)
{
    mCanPassThrough = true;
    mLives = 3;
    mBomb = nullptr;
    mTimer = 0;
    mState = NORMAL;
    mExplosionColidedWith = nullptr;
    mSkinID =0;
}

Player::~Player()
{
}

int Player::getSkinID() const
{
    return mSkinID;
}

void Player::setSkinID(int ID)
{
    mSkinID = ID;
}

Bomb *Player::placingBomb(BombExplosionNotification *notifier)
{
    if (mBomb == nullptr )
    {
        Bomb *bomb;
        if(mDirection == UP  && mIsMoving)
            bomb = new Bomb(getRow() +1, getColumn(), notifier, 2);
        else if(mDirection == LEFT && mIsMoving)
            bomb = new Bomb(getRow(), getColumn() +1, notifier, 2);
        else
            bomb = new Bomb(getRow(), getColumn(), notifier, 2);
        mBomb = bomb;
        return bomb;
    }
    return nullptr;
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
    mLives = mLives - 1;
}

Player::State Player::getState() const
{
    return mState;
}

bool Player::isMyBomb(GameObject *bomb)
{
    if (mBomb == bomb)
        return true;
    return false;
}

void Player::collision(GameObject *object)
{
    if (object->getType() == GameObject::EXPLOSION)
    {
        if(mExplosionColidedWith != object)
        {
            //ensure that we stop on the same coordinates as the explosion
            if(!isNextStepDifferentCell() && mState != DYEING)
            {
                mExplosionColidedWith = (Explosion*)object;
                mState = DYEING;
                reduceLives();
                stopObject();
                mTimer = 100;
            }
        }
    }
    else if (object->getType() == GameObject::BOMB)
    {
        if (!isMyBomb(object))
        {
            object->setDirection(mDirection);
            forceStopObject();
        }
    }
    else
    {
        GameObject::collision(object);
    }
}

void Player::setDirection(Direction direction)
{
    if (mState == NORMAL)
        GameObject::setDirection(direction);
}

void Player::move()
{
    if (mTimer != 0)
    {
        mTimer -= 1;
    }
    else
    {
        mState = NORMAL;
    }
    GameObject::move();
    // check if player is still in same cell as placed bomb
    if (mBomb != nullptr)
    {
        // checkif i have an intersection my bomb
        rava::traits::Rect bombRectangle;
        mBomb->getRectangle(bombRectangle);
        bombRectangle.shrink(1);
        rava::traits::Rect playerRectangle;
        getRectangle(playerRectangle);
        playerRectangle.shrink(1);

        if (!bombRectangle.intersect(playerRectangle))
            mBomb = nullptr;
    }
}

void Player::accept(IGameObjectVisitor *visitor) const
{
    visitor->visit(this);
}
