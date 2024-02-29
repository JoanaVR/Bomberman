#include "game/Blocks.h"

using namespace std;

Block::Block(bool isBreckable, int row, int column) : GameObject(row, column)
{
    mIsBreackable = isBreckable;
    mSpeed = 0;
    mCanPassThrough = false;
}


GameObject::ObjectType Block::getType() const
{
    if(mIsBreackable)
        return BLOCK;
    else
        return UNBREAKABLE_BLOCK;
}


