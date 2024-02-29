#include "DrawObject.h"
#include <Draw2D.h>
#include <traits.h>
#include "Draw2DTextureManager.h"

namespace draw
{



    void DrawObject::draw(SDL_Renderer *renderer, const GameObject* gameObject, const rava::traits::Rect& displayRect, double xRatio, double yRatio)
    {
        rava::traits::Rect boundingRect;
        gameObject->getRectangle(boundingRect);

        rava::traits::Rect rectangleToDraw(boundingRect.x1() * xRatio + displayRect.x1()
                                            , boundingRect.y1() * yRatio + displayRect.y1()
                                            , boundingRect.x2()* xRatio + displayRect.x1()
                                            , boundingRect.y2()* yRatio + displayRect.y1());

        //rava::traits::Color btnColor(0, 0, 0);
        //rava::draw2D::fill(renderer, rectangleToDraw, btnColor);
        rava::traits::Color btnColor(0, 0, 0);
        rava::draw2D::drawRect(renderer,rectangleToDraw, 2,btnColor);

        switch(gameObject->getType())
        {
            case GameObject::BLOCK:
                
                rava::draw2D::TextureManager::blendGlyphItem(renderer, "129", rectangleToDraw.get_size(),rectangleToDraw.x1_y1(), false);
                break;
            case GameObject::UNBREAKABLE_BLOCK:
                rava::draw2D::TextureManager::blendGlyphItem(renderer, "128", rectangleToDraw.get_size(),rectangleToDraw.x1_y1(), false);
                break;
            case GameObject::PLAYER:
                rava::draw2D::TextureManager::blendGlyphItem(renderer, "123", rectangleToDraw.get_size(),rectangleToDraw.x1_y1(), false);
                break;
            case GameObject::BOMB:
                rava::draw2D::TextureManager::blendGlyphItem(renderer, "126", rectangleToDraw.get_size(),rectangleToDraw.x1_y1(), false);
                break;
            case GameObject::POWERUP:
                rava::draw2D::TextureManager::blendGlyphItem(renderer, "125", rectangleToDraw.get_size(),rectangleToDraw.x1_y1(), false);
                break;
        }

        

       //Widget::draw(renderer);
    
    }
}
