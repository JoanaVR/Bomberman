#pragma once
#include "GameObject.h"


class IPlayerControl
{
    public:
    virtual void move (int playerID, GameObject::Direction directio) = 0;
    virtual void stop (int playerID) = 0;
    virtual void placeBomb (int playerID) = 0;

    protected:

};