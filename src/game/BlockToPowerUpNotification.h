#pragma once

class Block;
class BlockToPowerUpNotification
{
    public:
    virtual void createPowerUp(Block* block, Explosion* explsion) = 0;

};