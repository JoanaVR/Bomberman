#pragma once

#include <iostream>

class Bomb;

class BombExplosionNotification
{
    public:
    virtual void explode(int bombRow, int bombColumn, int explosionRadius) = 0;
};