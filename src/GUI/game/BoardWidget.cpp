#include <Draw2D.h>
#include <traits.h>
#include <Logging.h>
#include "Utils/GuiFactory.h"

#include "Application.h"
#include "gameDraw/GameDrawer.h"

namespace draw
{
#define WithToHeighRatio 3.2

    void BoardWidget::draw(SDL_Renderer *renderer)
    {
        auto p = absolutePosition();

        rava::traits::Rect boundingRect(p.x(), p.y(), p.x() + width(), p.y() + height());
        // rava::traits::Color btnColor(235, 124, 124);
        // rava::draw2D::fill(renderer, boundingRect, btnColor);

        Application::getInstance()->mGame->move();
        Widget::draw(renderer);
        Application::getInstance()->mGameDrawer->drawBoard(renderer, boundingRect);
    }

    bool BoardWidget::keyboardEvent(int key, int scancode, int action, int modifiers)
    {

        static std::map<int, int> keysMap = {{SDLK_UP, Game::K_UP},
                                                 {SDLK_DOWN, Game::K_DOWN},
                                                 {SDLK_RIGHT, Game::K_RIGHT},
                                                 {SDLK_LEFT, Game::K_LEFT},
                                                 {SDLK_a, Game::K_a},
                                                 {SDLK_s, Game::K_s},
                                                 {SDLK_d, Game::K_d},
                                                 {SDLK_w, Game::K_w},
                                                 {SDLK_KP_ENTER, Game::K_ENTER},
                                                 {SDLK_SPACE, Game::K_SPACE}};

        int currentKey = Game::K_UNDEFINED;
        auto f = keysMap.find(key);
        if(f != keysMap.end())
            currentKey = f->second;

        int currentAction = Game::UNDEFINED;
        if (action == SDL_PRESSED)
            currentAction = Game::PRESSED;
        else if (action == SDL_RELEASED)
            currentAction = Game::RELEASED;

        Application::getInstance()->mGame->keyboardEvent(currentKey, scancode, currentAction, modifiers);

        return true;
    }

}
