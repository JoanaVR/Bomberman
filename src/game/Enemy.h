#pragma once
#include "IPlayerControl.h"
#include "IEnemy.h"


class Enemy : public IEnemy
{
    public:
    Enemy(IPlayerControl* control, int playerID);
    void undateState(bool ismoving) override;
    int getPlayerID() const override;


    private:
    IPlayerControl* mControl;
    bool mIsMoving;
    int mID;

};