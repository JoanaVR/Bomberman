#pragma once

#include <iostream>

class Bomb;

class BombExplosionNotification
{
    public:
    virtual void explode(Bomb* bomb) = 0;
};