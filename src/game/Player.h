#pragma once
#include "GameObject.h"


class Player: public GameObject
{

    public:
    Player(int row, int column);
    ~Player();
    GameObject::ObjectType getType() const; 
    int getLives();
    void reduceLives();
    void placingBomb(GameObject* bomb);
    void collision(GameObject* object) override;
    virtual void move() override;

    private:
    int mLives;
    GameObject* mBomb;
    bool isMyBomb(GameObject* bomb);
    
};