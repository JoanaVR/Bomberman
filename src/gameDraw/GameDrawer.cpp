#include "GameDrawer.h"
#include <Draw2D.h>
#include <traits.h>

namespace draw
{
    GameDrawer::GameDrawer(std::shared_ptr<Board> b)
    {
        mBoard = b;
    }

    GameDrawer::~GameDrawer()
    {
        mBoard.reset();
    }


    void GameDrawer::drawBoard(SDL_Renderer *gameDrawer, const rava::traits::Rect& boardRect)
    {

        rava::traits::Color btnColor(235, 235, 235);
        rava::draw2D::fill(gameDrawer, boardRect, btnColor);
        drawObjects(gameDrawer,boardRect);
        mBoard->move();

    }

    void GameDrawer::drawObjects(SDL_Renderer *gameDrawer, const rava::traits::Rect& boardRect)
    {
        double xRatio = boardRect.width() / static_cast<double>(mBoard->getWidth());
        double yRatio = boardRect.height() /  static_cast<double>(mBoard->getHight()) ;
        DrawObject drawVisitor(gameDrawer, boardRect, xRatio, yRatio);
        for(int i = 0; i < mBoard->getGameObjectsSize(); i++)
        {
            //DrawObject::draw(gameDrawer,mBoard->getObject(i), boardRect, xRatio, yRatio);
            mBoard->getObject(i)->accept(&drawVisitor);
            
        }

    }

 

}
