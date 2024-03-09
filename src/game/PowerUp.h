#pragma once
#include "GameObject.h"
#include "game/Explosion.h"

class PowerUp : public GameObject
{
    public:
    enum PowerUpType
    {
        INCREASE_PLAYER_SPEED,
        KICK_BOMB,
        ENHANCE_EPLOSION,
        PLACE_MULTIPLE_BOMBS,
        NO_POWERUP
    };

    PowerUp(int row, int column, PowerUpType type);
    GameObject::ObjectType getType() const override; 
    void collision(GameObject* object) override;
    void setExplosion(Explosion* explosion);

    private:
    PowerUpType mPowerUpType;
    Explosion* mExplosion;

};