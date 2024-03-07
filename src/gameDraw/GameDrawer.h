#pragma once

#include <vector>
#include <Widget.h>
#include "DrawObject.h"
#include "game/Board.h"

namespace draw
{

    class GameDrawer
    {
        public:

        GameDrawer(Board* b);
        ~GameDrawer();
        std::vector<DrawObject *> mObjectsToDraw;
        void drawBoard(SDL_Renderer *gameDrawer, const rava::traits::Rect& boardRect);
        void drawObjects(SDL_Renderer *gameDrawer, const rava::traits::Rect& boardRect);

        private:
        Board* mBoard;

    };

}