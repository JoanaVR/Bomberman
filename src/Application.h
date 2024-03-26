#pragma once

#include <memory>

#include <SDL3/SDL.h>
#include "GUI/game/game_screen.h"

#include <DisplayScreen.h>
#include <ModalDialog.h>
#include "AppBase.h"

#include "game/Board.h"
#include "gameDraw/GameDrawer.h"
#include "game/Player.h"
#include "game/Game.h"


class Application : public rava::app::AppBase
{
	void onEvent(SDL_Event &event) override;
	void onSizeChange(int screenW, int screenH) override;

	friend AppBase *rava::app::createApplication(SDL_Renderer *ren, SDL_Window *w, int screenW, int screenH);
	friend void rava::app::destroyApplication(AppBase *);

	static Application *m_sharedApplication;

	std::shared_ptr<rava::gui::GamaScreen> m_gameScreen;
	Application(SDL_Renderer *r, SDL_Window *w, int screenW, int screenH, const char* svgLogo);
	~Application();


	
public:
	static Application *getInstance()
	{
		if (!m_sharedApplication)
		{
			throw std::logic_error("The application is null!!");
		}
		return m_sharedApplication;
	}
	

	
    void newGame (bool isMultiplayer);
	void onGameOver();


	std::shared_ptr<rava::gui::GamaScreen> getGameScreen() const { return m_gameScreen; }




	SDL_Renderer *m_renderer;
	int	mScreenW; 
	int mScreenH;
	std::shared_ptr<draw::GameDrawer> mGameDrawer;
	std::shared_ptr<Game> mGame;

private:
	
	SDL_Window *window;
	

};
