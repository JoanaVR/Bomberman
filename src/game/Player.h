#pragma once
#include "GameObject.h"
#include "BombExplosionNotification.h"
#include "Bomb.h"
#include "Explosion.h"


class Player: public GameObject
{
    public:
    enum State
    {
        NORMAL,
        DYEING
    };
    
    Player(int row, int column);
    ~Player();
    GameObject::ObjectType getType() const; 
    int getLives() const;
    void reduceLives();
    Bomb* placingBomb(BombExplosionNotification* notifier);
    void collision(GameObject* object) override;
    virtual void move() override;
    State getState() const;
    void accept(IGameObjectVisitor* visitor) const override;
    virtual void setDirection(Direction direction) override;
    int getSkinID() const;
    void setSkinID(int ID);
    void setEnemy(bool isEnemy);
    bool isEnemy();
    int getKimkBombPowerUpNumber()const;
    int getEnhancedBombPowerUpNumber()const;


    private:
    int mLives;
    GameObject* mBomb;
    GameObject* mBombJustPlacedDown;
    bool isMyBomb(GameObject* bomb);
    State mState;
    int mTimer;
    Explosion* mExplosionColidedWith;
    int mSkinID;
    int mKickBombPowerup;
    int mSpeedPowerUpTimer;
    int mEnhancedBombs;
    bool mIsEnemy;
    
};