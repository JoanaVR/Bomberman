#pragma once
#include "GameObject.h"
#include "PowerUp.h"
#include "BlockToPowerUpNotification.h"

class Block: public GameObject
{
    public:
    Block(bool isBreckable, int row, int column, PowerUp::PowerUpType powerUpType, BlockToPowerUpNotification* notifier);
    GameObject::ObjectType getType() const override;
    void collision(GameObject* object) override;
    PowerUp::PowerUpType getPowerUpType() const;

    private:
    bool mIsBreackable;
    PowerUp::PowerUpType mPowerupType;
    BlockToPowerUpNotification* mNotifier;
    
};