#pragma once
#include "game/GameObject.h"
#include "game/IGameObjectVisitor.h"
#include <Widget.h>

namespace draw
{

    class DrawObject : public IGameObjectVisitor
    {
    public:
        DrawObject(SDL_Renderer *renderer, const rava::traits::Rect &displayRect, double xRatio, double yRatio);
        static void draw(SDL_Renderer *renderer, const GameObject *gameObject, const rava::traits::Rect &displayRect, double xRatio, double yRatio);
        void visit(const GameObject *object) override;
        void visit(const Player *player) override;

    private:
        SDL_Renderer *mRenderer;
        rava::traits::Rect mDisplayRect;
        double mXRatio;
        double mYRatio;
    };

}