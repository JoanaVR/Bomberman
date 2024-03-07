#pragma once

#include <Widget.h>

#include "game/Board.h"
#include "game/Player.h"

namespace draw
{
    class BoardWidget : public rava::gui::Widget
    {

    public:
        void draw(SDL_Renderer *renderer) override;

        bool keyboardEvent(int key, int scancode, int action, int modifiers ) override;
        
    };

}
