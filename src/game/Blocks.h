#pragma once
#include "GameObject.h"

class Block: public GameObject
{
    public:
    Block(bool isBreckable, int row, int column);
    GameObject::ObjectType getType() const override;
    
    private:
    bool mIsBreackable;
     
    
};