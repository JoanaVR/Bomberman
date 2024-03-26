#pragma once

#include <vector>
#include <functional>
#include "GameObject.h"
#include "Blocks.h"
#include "Player.h"
#include "Bomb.h"
#include "BombExplosionNotification.h"
#include "BlockToPowerUpNotification.h"

class Board: public BombExplosionNotification, public BlockToPowerUpNotification
{
    public:

    Board(int row, int column);
    Board& operator = (const Board& b);

    int getRows () const;
    int getColumns()const;
    int getWidth() const;
    int getHight() const;
    int getBoardSize()const;
    void addObject(GameObject* object);
    int getGameObjectsSize() const;
    const GameObject* getObject(int index) const;
    std::vector<GameObject*> getAllCollisionsWithCell(int row, int column);
    GameObject::ObjectType getObjectType(int row, int column);
    Player* getPlayer();
    std::vector<std::pair<GameObject*, GameObject*>> findCollisions();
    void move();
    void stopOutOfBoardObjects();
    void removeObject(GameObject* object);
    bool isObjectInBombRadius(int bombRow, int bombColumn, int explosionRadius, int objectRow, int objectColumn);
    void explode(Bomb* bomb) override;
    void createPowerUp(Block* block, Explosion* explsion) override;

    private:
    std::vector<GameObject*> mGameObjects;

    int mRows;
    int mColumns;
    int mWidth;
    int mHight;
    
    
};
