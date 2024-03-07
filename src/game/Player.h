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
    int getLives();
    void reduceLives();
    Bomb* placingBomb(BombExplosionNotification* notifier);
    void collision(GameObject* object) override;
    virtual void move() override;
    State getState() const;
    void accept(IGameObjectVisitor* visitor) const override;
    virtual void setDirection(Direction direction) override;



    private:
    int mLives;
    GameObject* mBomb;
    bool isMyBomb(GameObject* bomb);
    State mState;
    int mTimer;
    Explosion* mExplosionColidedWith;

    
};