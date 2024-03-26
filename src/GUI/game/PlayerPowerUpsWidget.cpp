#include <Draw2D.h>
#include <traits.h>
#include "Draw2DTextureManager.h"
#include "PlayerPowerUpsWidget.h"
#include "game/Player.h"
#include "Application.h"

namespace draw
{
    void PlayerPowerUpsWidget::draw(SDL_Renderer *renderer)
    {
        auto p = absolutePosition();
        rava::traits::Rect boundingRect(p.x(), p.y(), p.x() + width(), p.y() + height());
        // rava::traits::Color btnColor(255, 255, 255);
        // rava::draw2D::fill(renderer, boundingRect, btnColor);
        drawPowerUpText(renderer, boundingRect);
    }

    void PlayerPowerUpsWidget::setPowerUps(int playerID)
    {
        mPlayerID = playerID;
        mTexture.release();
        const auto *player = Application::getInstance()->mGame->getPlayer(playerID);
        std::string numOfLives = std::to_string(player->getLives());
        std::string kickBomb = std::to_string(player->getKimkBombPowerUpNumber());
        std::string enhancedBombs = std::to_string(player->getEnhancedBombPowerUpNumber());
        mText = "Lives: " + numOfLives + " Kick Bomb: " + kickBomb + " Enhanced Bombs: " + enhancedBombs;
    }

    void PlayerPowerUpsWidget::drawPowerUpText(SDL_Renderer *renderer, const rava::traits::Rect &r)
    {
        if (mPlayerID > -1)
        {
            const auto *player = Application::getInstance()->mGame->getPlayer(mPlayerID);
            std::string numOfLives = std::to_string(player->getLives());
            std::string kickBomb = std::to_string(player->getKimkBombPowerUpNumber());
            std::string enhancedBombs = std::to_string(player->getEnhancedBombPowerUpNumber());
            auto tmpText = "Lives: " + numOfLives + " Kick Bomb: " + kickBomb + " Enhanced Bombs: " + enhancedBombs;
            if (mTexture.tex == nullptr || tmpText != mText)
            {
                mText = tmpText;
                mTexture.release();

                SDL_Color black = {0, 0, 0};

                mTexture.tex = rava::draw2D::getTexAndRect(renderer, mText.c_str(), "", (int)(r.height()),
                                                           black, mTexture.w, mTexture.h);
            }
        }

        SDL_Rect src_rect{0, 0, mTexture.w, mTexture.h};
        SDL_Rect dest_rect{r.x1() - ((mTexture.w - r.width())) / 2, r.y1() - ((mTexture.h - r.height())) / 2, mTexture.w, mTexture.h};

        mTexture.draw(renderer, &src_rect, &dest_rect);
    }

}