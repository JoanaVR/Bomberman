#pragma once

#include <Widget.h>
#include <string>
#include <Draw2DTexture.h>
#include "game/Player.h"

namespace draw
{
    class PlayerPowerUpsWidget : public rava::gui::Widget
    {
    public:
        void draw(SDL_Renderer *renderer) override;
        void setPowerUps(int playerID);

    private:
        void drawPowerUpText(SDL_Renderer *renderer, const rava::traits::Rect &r);

        std::string mText;
        rava::draw2D::Texture mTexture;
        int mPlayerID = -1;

    };

}