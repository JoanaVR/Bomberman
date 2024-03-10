#include "DrawObject.h"
#include <Draw2D.h>
#include <traits.h>
#include "Draw2DTextureManager.h"
#include "game/Player.h"
#include "game/PowerUp.h"

namespace draw
{
    DrawObject::DrawObject(SDL_Renderer *renderer, const rava::traits::Rect &displayRect, double xRatio, double yRatio) : mRenderer(renderer), mDisplayRect(displayRect),
                                                                                                                          mXRatio(xRatio), mYRatio(xRatio)
    {}

    void DrawObject::draw(SDL_Renderer *renderer, const GameObject *gameObject, const rava::traits::Rect &displayRect, double xRatio, double yRatio)
    {
        rava::traits::Rect boundingRect;
        gameObject->getRectangle(boundingRect);

        rava::traits::Rect rectangleToDraw(boundingRect.x1() * xRatio + displayRect.x1(), boundingRect.y1() * yRatio + displayRect.y1(), boundingRect.x2() * xRatio + displayRect.x1(), boundingRect.y2() * yRatio + displayRect.y1());

        // rava::traits::Color btnColor(0, 0, 0);
        // rava::draw2D::fill(renderer, rectangleToDraw, btnColor);
        rava::traits::Color btnColor(0, 0, 0);
        rava::draw2D::drawRect(renderer, rectangleToDraw, 2, btnColor);

        switch (gameObject->getType())
        {
        case GameObject::BLOCK:

            rava::draw2D::TextureManager::blendGlyphItem(renderer, "block", rectangleToDraw.get_size(), rectangleToDraw.x1_y1(), false);
            break;
        case GameObject::UNBREAKABLE_BLOCK:
            rava::draw2D::TextureManager::blendGlyphItem(renderer, "unbreackableBlock", rectangleToDraw.get_size(), rectangleToDraw.x1_y1(), false);
            break;
        case GameObject::BOMB:
            rava::draw2D::TextureManager::blendGlyphItem(renderer, "bomb", rectangleToDraw.get_size(), rectangleToDraw.x1_y1(), false);
            break;
        case GameObject::EXPLOSION:
            rava::draw2D::TextureManager::blendGlyphItem(renderer, "explosion", rectangleToDraw.get_size(), rectangleToDraw.x1_y1(), false);
            break;
        }

        // Widget::draw(renderer);
    }

    void DrawObject::visit(const GameObject *object)
    {
        draw(mRenderer,object, mDisplayRect, mXRatio, mYRatio);
    }
    void DrawObject::visit(const Player *player)
    {
        rava::traits::Rect boundingRect;
        player->getRectangle(boundingRect);

        rava::traits::Rect rectangleToDraw(boundingRect.x1() * mXRatio + mDisplayRect.x1(), boundingRect.y1() * mYRatio + mDisplayRect.y1(), boundingRect.x2() * mXRatio + mDisplayRect.x1(), boundingRect.y2() * mYRatio + mDisplayRect.y1());

        if(player->getState() == Player::NORMAL)
        {
            int id = player->getSkinID();
            if(id == 0)
                rava::draw2D::TextureManager::blendGlyphItem(mRenderer, "redPlayer", rectangleToDraw.get_size(), rectangleToDraw.x1_y1(), false);
            else if (id == 1)
                rava::draw2D::TextureManager::blendGlyphItem(mRenderer, "bluePlayer", rectangleToDraw.get_size(), rectangleToDraw.x1_y1(), false);
        }
        else
            rava::draw2D::TextureManager::blendGlyphItem(mRenderer, "player", rectangleToDraw.get_size(), rectangleToDraw.x1_y1(), false);
        //draw(mRenderer, (GameObject*)player, mDisplayRect, mXRatio, mYRatio);
    }

    void DrawObject::visit(const PowerUp *powerUp)
    {
        rava::traits::Rect boundingRect;
        powerUp->getRectangle(boundingRect);

        rava::traits::Rect rectangleToDraw(boundingRect.x1() * mXRatio + mDisplayRect.x1(), boundingRect.y1() * mYRatio + mDisplayRect.y1(), boundingRect.x2() * mXRatio + mDisplayRect.x1(), boundingRect.y2() * mYRatio + mDisplayRect.y1());
        PowerUp::PowerUpType type = powerUp->getPowerUpType();
            if(type == PowerUp::KICK_BOMB)
                rava::draw2D::TextureManager::blendGlyphItem(mRenderer, "kickBombPowerUp", rectangleToDraw.get_size(), rectangleToDraw.x1_y1(), false);
            else if(type == PowerUp::INCREASE_PLAYER_SPEED)
                rava::draw2D::TextureManager::blendGlyphItem(mRenderer, "increasePlayerSpeedPowerUp", rectangleToDraw.get_size(), rectangleToDraw.x1_y1(), false);
            else if(type == PowerUp::ENHANCE_EPLOSION)
                rava::draw2D::TextureManager::blendGlyphItem(mRenderer, "enhanceExplosionPowerUp", rectangleToDraw.get_size(), rectangleToDraw.x1_y1(), false);
            else if(type == PowerUp::PLACE_MULTIPLE_BOMBS)
                rava::draw2D::TextureManager::blendGlyphItem(mRenderer, "placeMultipleBombsPowerUp", rectangleToDraw.get_size(), rectangleToDraw.x1_y1(), false);    
    }



}
