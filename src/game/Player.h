#pragma once
#include "GameObject.h"


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
    void placingBomb(GameObject* bomb);
    void collision(GameObject* object) override;
    virtual void move() override;
    State getState() const;
    void accept(IGameObjectVisitor* visitor) const override;


    private:
    int mLives;
    GameObject* mBomb;
    bool isMyBomb(GameObject* bomb);
    State mState;
    int mTimer;

    
};