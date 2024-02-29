#include "Player.h"
#include "Bomb.h"

using namespace std;

Player::Player(int row, int column) : GameObject(row, column)
{
    mCanPassThrough = true;
    mLives = 3;
}

Player::~Player()
{
    

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

