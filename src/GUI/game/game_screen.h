#pragma once
#include <DisplayScreen.h>
#include <ModalDialog.h>

#include <Label.h>
#include <Checkbox.h>
#include <Button.h>
#include <Textbox.h>
#include <traits.h>

#include <Draw2D.h>

#include <memory>

#include <iostream>

#include <SDL3/SDL.h>
#include <Draw2D.h>
#include <Draw2DSurface.h>
#include <Draw2DTextureManager.h>
#include "game/Board.h"
#include "GUI/game/BoardWidget.h"
#include "GUI/draw_strategies_ids.hpp"


namespace rava::gui
{

    struct NavigationBar : public rava::gui::Widget
    {

        void draw(SDL_Renderer *renderer) override
        {

            if (visible() == false)
                return;

            typedef rava::traits::Color color;

            // the painting rectangle
            rava::traits::Rect boundingRect(0, 0, width(), height());
            rava::traits::Color btnColor(222, 222, 222);

            rava::draw2D::fill(renderer, boundingRect, btnColor);
        }
    };

    struct GlyphWidgetModel
    {
        const char* m_glyph_index_1 = "0";
        const char* m_glyph_index_2 = "1";
        const char* m_glyph_index_3 = "2";
        const char* m_glyph_index_4 = "3";
    };

    struct GlyphButtonModel : public GlyphWidgetModel
    {
        std::function<void(int btnId)> callBack_;
        GlyphButtonModel(std::function<void(int)> callBack) : callBack_(callBack)
        {
        }

        bool Pushed() const
        {
            return m_pushed;
        }

        void SetPushed(bool pushed)
        {

            m_pushed = pushed;
        }

        bool onMouseEvent(bool down)
        {
            if (down)
            {
                SetPushed(true);
            }
            else if (down == false && Pushed())
            {

                SetPushed(false);
                if (callBack_)
                    callBack_(Id());
            }
            return true;
        }

        void SetText(const std::string &text)
        {
            m_text = text;
        }

        std::string Text() const
        {
            return m_text;
        }

        int Id()
        {
            return m_id;
        }

        void SetId(int id)
        {
            m_id = id;
        }

    private:
        bool m_pushed = false;
        std::string m_text;
        int m_id;
    };

    struct TabButtonType : public rava::gui::Widget, public GlyphButtonModel
    {

        TabButtonType(const std::function<void(int)> callBack) : GlyphButtonModel(callBack)
        {
        }

        bool mouseButtonEvent(const rava::traits::Point &p, int button, bool down, int modifiers) override
        {
            onMouseEvent(down);
            return true;
        }

        void draw(SDL_Renderer *renderer) override
        {
            rava::traits::Rect boundingRect(0, 0, width(), height());
            rava::traits::Rect total_rect = boundingRect;
            rava::traits::Point pnt(position().x_, position().y_);

            // draw border
            boundingRect.shrink(1);

            if (Pushed())
            {
                if (rava::draw2D::TextureManager::blendCachedItem(renderer, TAB_BOTTOM_BUTTON_PAINT_ID, total_rect.get_size(), pnt) == false)
                {
                    rava::draw2D::Surface sp(total_rect.get_size());
                    draw2D::fillRoundRectWithBorder(sp.getSurface(), boundingRect, 2,{0,127, 0, 255}, rava::traits::Color(255, 255, 255, 200));
                    rava::draw2D::TextureManager::addSerfaceToChace(renderer, TAB_BOTTOM_BUTTON_PAINT_ID, sp.getSurface());
                    rava::draw2D::TextureManager::blendCachedItem(renderer, TAB_BOTTOM_BUTTON_PAINT_ID, total_rect.get_size(), pnt);
                }

                rava::draw2D::TextureManager::blendGlyphItem(renderer, m_glyph_index_1, boundingRect.get_size(), pnt);
            }
            else
            {
                /*
                if(rava::draw2D::TextureManager::blendCachedItem(TAB_BOTTOM_BUTTON_SELECTED_PAINT_ID, total_rect.get_size(), pnt) == false)
                {
                    rava::draw2D::Surface sp(  total_rect.get_size());
                    draw2D::fillRoundRectWithBorder(sp.getSurface(), boundingRect,1,{0,127, 0, 255},rava::traits::Color(181,206,239),255);
                    rava::draw2D::TextureManager::addSerfaceToChace(TAB_BOTTOM_BUTTON_SELECTED_PAINT_ID, sp.getSurface());
                    rava::draw2D::TextureManager::blendCachedItem(TAB_BOTTOM_BUTTON_SELECTED_PAINT_ID, total_rect.get_size(), pnt);
                }
                */
                rava::draw2D::TextureManager::blendGlyphItem(renderer, m_glyph_index_2, boundingRect.get_size(), pnt);
            }

            if (focused())
            {
                rava::traits::Rect focusedRect(0, 0, width(), height());
                focusedRect.shrink(1);
                // rava::draw2D::TextureManager::roundRectangle( focusedRect, 12, 2, rava::traits::Color(RED_FOCUSED_COLOR, GREEN_FOCUSED_COLOR, BLUE_FOCUSED_COLOR) );
            }
        }
    };

    class GamaScreen : public DisplayScreen
    {
    public:
        GamaScreen(SDL_Window *pwindow, int rwidth, int rheight, SDL_Renderer *renderer);
        ~GamaScreen();

        virtual void draw(SDL_Renderer *renderer);
        void onResize(int newScreenW, int newScreenH) override;

    private:
        void btnClick(int btnId);

        std::shared_ptr<NavigationBar> m_navBar;

	    std::shared_ptr< TabButtonType > m_menuTabButton;

        std::shared_ptr<draw::BoardWidget> mBoardWidget;

        SDL_Renderer *m_renderer;
        
    };

}
