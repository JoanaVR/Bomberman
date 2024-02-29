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


    private:
    int mLives;
    
};