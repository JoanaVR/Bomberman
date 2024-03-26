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

        if(Application::getInstance()->mGame)
        {
            Application::getInstance()->mGame->move();
            Widget::draw(renderer);
            Application::getInstance()->mGameDrawer->drawBoard(renderer, boundingRect);
        }
    }

    bool BoardWidget::keyboardEvent(int key, int scancode, int action, int modifiers)
    {
        /*
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
        if (f != keysMap.end())
            currentKey = f->second;

        int currentAction = Game::UNDEFINED;
        if (action == SDL_PRESSED)
            currentAction = Game::PRESSED;
        else if (action == SDL_RELEASED)
            currentAction = Game::RELEASED;

        Application::getInstance()->mGame->keyboardEvent(currentKey, scancode, currentAction, modifiers);

        return true;*/

        static std::map<int, bool> currentKeysPlayer1 = {{SDLK_UP, false},
                                                     {SDLK_DOWN, false},
                                                     {SDLK_RIGHT, false},
                                                     {SDLK_LEFT, false}};

    static std::map<int, bool> currentKeysPlayer2 = {{SDLK_w, false},
                                                     {SDLK_s, false},
                                                     {SDLK_d, false},
                                                     {SDLK_a, false}};

        if (action == SDL_PRESSED)
        {
            LOG_MIL("keyboardEvent pressed, key: %d", key);
            switch (key)
            {
            case SDLK_UP:
            {
                currentKeysPlayer1[key] = true;
                Application::getInstance()->mGame->move(0, GameObject::UP);
            }
            break;
            case SDLK_DOWN:
            {
                currentKeysPlayer1[key] = true;
                Application::getInstance()->mGame->move(0, GameObject::DOWN);
            }
            break;
            case SDLK_RIGHT:
            {
                currentKeysPlayer1[key] = true;
                Application::getInstance()->mGame->move(0, GameObject::RIGHT);
            }
            break;
            case SDLK_LEFT:
            {
                currentKeysPlayer1[key] = true;
                Application::getInstance()->mGame->move(0, GameObject::LEFT);
            }
            break;
            case SDLK_KP_ENTER:
            {
                Application::getInstance()->mGame->placeBomb(0);
            }
            break;
            case SDLK_w:
            {
                currentKeysPlayer2[key] = true;
                Application::getInstance()->mGame->move(1, GameObject::UP);
            }
            break;
            case SDLK_s:
            {
                currentKeysPlayer2[key] = true;
                Application::getInstance()->mGame->move(1, GameObject::DOWN);
            }
            break;
            case SDLK_d:
            {
                currentKeysPlayer2[key] = true;
                Application::getInstance()->mGame->move(1, GameObject::RIGHT);
            }
            break;
            case SDLK_a:
            {
                currentKeysPlayer2[key] = true;
                Application::getInstance()->mGame->move(1, GameObject::LEFT);
            }
            break;
            case SDLK_SPACE:
            {
                Application::getInstance()->mGame->placeBomb(1);
            }
            break;
            default:
                break;
            }
        }
        else if (action == SDL_RELEASED)
        {
            switch (key)
            {
            case SDLK_UP:
            case SDLK_DOWN: 
            case SDLK_RIGHT: 
            case SDLK_LEFT:
            {
                currentKeysPlayer1[key] = false;
            }
            break;
            case SDLK_w:
            case SDLK_s:
            case SDLK_d:
            case SDLK_a:
            {
                currentKeysPlayer2[key] = false;
            }
            break;
            }
            
            LOG_MIL("keyboardEvent RELESED, key: %d", key);
            bool havePressedDirectionPlayer1 = false;
            for (auto &i : currentKeysPlayer1)
            {
                havePressedDirectionPlayer1 |= i.second;
            }
            if (!havePressedDirectionPlayer1)
                Application::getInstance()->mGame->stop(0);

            bool havePressedDirectionPlayer2 = false;
            for (auto &i : currentKeysPlayer2)
            {
                havePressedDirectionPlayer2 |= i.second;
            }
            if (!havePressedDirectionPlayer2)
                Application::getInstance()->mGame->stop(1);
        }
        return true;
    }

}
