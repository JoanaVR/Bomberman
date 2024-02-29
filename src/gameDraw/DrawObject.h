#pragma once
#include "game/GameObject.h"
#include <Widget.h>

namespace draw
{

    class DrawObject
    {
        public:

        static void draw(SDL_Renderer *renderer, const GameObject* gameObject, const rava::traits::Rect& displayRect, double xRatio, double yRatio);

        
        
    };

}