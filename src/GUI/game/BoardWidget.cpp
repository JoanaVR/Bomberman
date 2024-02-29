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

        Widget::draw(renderer);
        Application::getInstance()->mGameDrawer->drawBoard(renderer, boundingRect);
    }

    bool BoardWidget::keyboardEvent(int key, int scancode, int action, int modifiers)
    {
        static std::map<int, bool> currentKeys = {{SDLK_UP, false}, 
                                                  {SDLK_DOWN, false}, 
                                                  {SDLK_RIGHT, false}, 
                                                  {SDLK_LEFT, false} };

        if (action == SDL_PRESSED)
        {
            LOG_MIL("keyboardEvent pressed, key: %d", key);    
            currentKeys[key] = true;
            switch (key)
            {
            case SDLK_UP:
            {
                
                
                Application::getInstance()->mPlayer->setDirection(GameObject::UP);
            }
            break;
            case SDLK_DOWN:
            {
                Application::getInstance()->mPlayer->setDirection(GameObject::DOWN);
            }
            break;
            case SDLK_RIGHT:
            {
                Application::getInstance()->mPlayer->setDirection(GameObject::RIGHT);
            }
            break;
            case SDLK_LEFT:
            {
                Application::getInstance()->mPlayer->setDirection(GameObject::LEFT);
            }
            break;
            case SDLK_KP_ENTER:
            {
            }
            break;
            case SDLK_SPACE:
            {
            }
            break;
            case SDLK_a:
            {
                Application::getInstance()->m_board->placeBomb(Application::getInstance()->mPlayer->getRow(), Application::getInstance()->mPlayer->getColumn());
            }
            break;

            case SDLK_DELETE:
            {
            }
            break;
            }
        }
        else if (action == SDL_RELEASED)
        {
            currentKeys[key] = false;
            LOG_MIL("keyboardEvent RELESED, key: %d", key);
            bool havePressedDirection = false;    
            for(auto &i : currentKeys )
            {
                havePressedDirection |= i.second;
            }
            if(!havePressedDirection)
                Application::getInstance()->mPlayer->stopObject();
        }
        return true;
    }

}
