#pragma once
#include "IPlayerControl.h"


class IEnemy
{
    public:
    virtual void undateState(bool ismoving) = 0;
    virtual int getPlayerID() const = 0 ;

};