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

        GameDrawer(std::shared_ptr<Board> b);
        ~GameDrawer();
        std::vector<DrawObject *> mObjectsToDraw;
        void drawBoard(SDL_Renderer *gameDrawer, const rava::traits::Rect& boardRect);
        void drawObjects(SDL_Renderer *gameDrawer, const rava::traits::Rect& boardRect);

        private:
        std::shared_ptr<Board> mBoard;

    };

}