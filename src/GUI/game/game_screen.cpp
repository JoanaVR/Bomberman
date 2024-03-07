#include "GUI/game/game_screen.h"

#include "game/Board.h"
#include "Application.h"
#include "GUI/game/BoardWidget.h"
#include "GUI/GlyphDefs.h"
#include "Utils/GuiFactory.h"
#include "GUI/game/menu_screen.h"
#include <FileManager.h>

namespace rava::gui
{

    GamaScreen::GamaScreen(SDL_Window *pwindow, int rwidth, int rheight, SDL_Renderer *renderer)
        : DisplayScreen(rava::traits::Size(rwidth, rheight)), m_renderer(renderer)
    {
        m_navBar.reset(new NavigationBar());
        auto navBarRect = utils::GuiFactory::getNavigationRect();
        m_navBar->setPosition(rava::traits::Point(navBarRect.x1(), navBarRect.y1()));
        m_navBar->setSize(rava::traits::Size(navBarRect.width(), navBarRect.height()));

        add(m_navBar);

        m_menuTabButton.reset(new TabButtonType([this](int id)
                                                { btnClick(id); }));

        m_menuTabButton->m_glyph_index_1 = APP_TAB_MENU_GLYPH;
        m_menuTabButton->m_glyph_index_2 = APP_TAB_MENU_SELECTED_GLYPH;
        m_menuTabButton->SetId(GAME_FORM_HOME_BUTTON_RES_ID);


        add(m_menuTabButton);

      
        mBoardWidget.reset(new draw::BoardWidget());
        add(mBoardWidget);

    }

    void GamaScreen::onResize(int newScreenW, int newScreenH)
    {
        rava::gui::DisplayScreen::setSize({newScreenW, newScreenH});
        //auto board = Application::getInstance()->mGame->getBoard();
        auto boardRect = utils::GuiFactory::getBoardRect();
        mBoardWidget->setSize({boardRect.width(), boardRect.height()});
        mBoardWidget->setPosition(boardRect.x1_y1());
        // mBoardWidget->setBottleSize(mBoardWidget->getBottleWidth(maxBottlesOnRow));

        auto navBarRect = utils::GuiFactory::getNavigationRect();
        m_navBar->setPosition(rava::traits::Point(navBarRect.x1(), navBarRect.y1()));
        m_navBar->setSize(rava::traits::Size(navBarRect.width(), navBarRect.height()));

        auto btnHeigh = utils::GuiFactory::getButnHight();
        int topPadding = (navBarRect.height() - btnHeigh) / 2;

        m_menuTabButton->setPosition(rava::traits::Point(navBarRect.x1() + topPadding, navBarRect.y1() + topPadding));
        m_menuTabButton->setSize(rava::traits::Size(btnHeigh, btnHeigh));

    }

    GamaScreen::~GamaScreen()
    {
    }

    void GamaScreen::btnClick(int btnId)
    {
        switch (btnId)
        {
        case GAME_FORM_HOME_BUTTON_RES_ID:
            MenuDialogFactory::create(m_renderer);
            break;
        }
    }


    void GamaScreen::draw(SDL_Renderer *renderer)
    {
        rava::traits::Rect boundingRect(0,0, width(), height());
        rava::traits::Color btnColor(127, 127, 127);
        rava::draw2D::fill(renderer, boundingRect, btnColor);
        DisplayScreen::draw(renderer);

    }

}
