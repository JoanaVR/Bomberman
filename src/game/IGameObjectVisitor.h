#pragma once

class GameObject;
class Player;
class IGameObjectVisitor
{
    public:
    virtual ~IGameObjectVisitor() = default;
    virtual void visit(const GameObject* object) = 0;
    virtual void visit(const Player* player) = 0;


};
