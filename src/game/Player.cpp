#include "Player.h"
#include "Bomb.h"
#include "BombExplosionNotification.h"
#include "PowerUp.h"

using namespace std;

Player::Player(int row, int column) : GameObject(row, column)
{
    mCanPassThrough = true;
    mIsMoving = false;
    mLives = 3;
    mBomb = nullptr;
    mBombJustPlacedDown =  nullptr;
    mTimer = 0;
    mState = NORMAL;
    mExplosionColidedWith = nullptr;
    mSkinID = 0;
    mKickBombPowerup = 0;
    mSpeedPowerUpTimer =0;
    mEnhancedBombs = 0;
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
    int bombRadius = 2;
    if(mEnhancedBombs > 0)
    {
        bombRadius = 10;
        mEnhancedBombs --;
    }
    if (mBomb == nullptr)
    {
        Bomb *bomb;
        if (mDirection == UP && mIsMoving)
            bomb = new Bomb(getRow() + 1, getColumn(), notifier, bombRadius);
        else if (mDirection == LEFT && mIsMoving)
            bomb = new Bomb(getRow(), getColumn() + 1, notifier, bombRadius);
        else
            bomb = new Bomb(getRow(), getColumn(), notifier, bombRadius);
        mBomb = bomb;
        mBombJustPlacedDown = bomb;
        //if there was a power up return bomb radius to normal after placing bomb
        bombRadius = 2;
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
        if (mExplosionColidedWith != object)
        {
            // ensure that we stop on the same coordinates as the explosion
            if (!isNextStepDifferentCell() && mState != DYEING)
            {
                mExplosionColidedWith = (Explosion *)object;
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
            if (mBombJustPlacedDown == object && mKickBombPowerup > 0)
            {
            object->setDirection(mDirection);
            mKickBombPowerup --;
            }
            forceStopObject();
        }        
}
    else if (object->getType() == GameObject::POWERUP)
    {
        switch (dynamic_cast<PowerUp *>(object)->getPowerUpType())
        {
        case PowerUp::KICK_BOMB:
            mKickBombPowerup += 5;
            break;
        case PowerUp::INCREASE_PLAYER_SPEED:
            mSpeedPowerUpTimer = 500;
            break;
        case PowerUp::ENHANCE_EPLOSION:
            mEnhancedBombs ++;
            break;
        case PowerUp::PLACE_MULTIPLE_BOMBS:
            break;
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
    {
        GameObject::setDirection(direction);
        if(mSpeedPowerUpTimer >0)
            mSpeed = mDefaultSpeed + 2;
    }
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
    mSpeedPowerUpTimer --;
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
