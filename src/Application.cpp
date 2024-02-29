

#include <SDL3/SDL.h>

#include "Application.h"
#include "game/Board.h"
// #include "GlyphDefs.hpp"
#include <FileManager.h>

#include "Draw2DTextureManager.h"
#include "Draw2D.h"
#include "FontCache.h"
#include "GUI/game/game_screen.h"
#include "Utils/GuiFactory.h"
#include "game/Level.h"

#include <thread>
#include "GUI/game/game_over_screen.h"
#include <fstream>
#include <iostream>
#include <string>

extern const char *gAppSplashScreen;

Application *Application::m_sharedApplication;

rava::app::AppBase *rava::app::createApplication(SDL_Renderer *ren, SDL_Window *w, int screenW, int screenH)
{
	if (Application::m_sharedApplication != NULL)
	{
		return Application::m_sharedApplication;
	}

	// draw logo!

	Uint32 time = SDL_GetTicks();

	Application::m_sharedApplication = new Application(ren, w, screenW, screenH, gAppSplashScreen);
	utils::GuiFactory::init();
	utils::GuiFactory::load(screenW, screenH);
	Application::m_sharedApplication->m_gameScreen.reset(new rava::gui::GamaScreen(w, screenW, screenH, ren));
	Application::m_sharedApplication->m_currentScreen = Application::m_sharedApplication->m_gameScreen;

#define T_INTERVAL 1000
	time = SDL_GetTicks() - time;
	if (time < T_INTERVAL)
	{
		time = T_INTERVAL - time;
		if (time > 0 && time < T_INTERVAL)
			std::this_thread::sleep_for(std::chrono::milliseconds(time));
	}
	return Application::m_sharedApplication;
}

Application::Application(SDL_Renderer *ren, SDL_Window *w, int screenW, int screenH, const char *svgLogo) : AppBase(ren, screenW, screenH, svgLogo, "glyphs.dat"), m_renderer(ren), window(w)
{
	mScreenW = screenW;
	mScreenH = screenH;
	// m_board.reset(new Board(5,5));
	newGame();
}

void rava::app::destroyApplication(AppBase *app)
{
	delete app;
	utils::GuiFactory::finalize();
}

void Application::onEvent(SDL_Event &event)
{
	AppBase::onEvent(event);
}

void Application::onSizeChange(int screenW, int screenH)
{
	mScreenW = screenW;
	mScreenH = screenH;
	utils::GuiFactory::load(screenW, screenH);
	m_gameScreen->onResize(screenW, screenH);
}

Application::~Application()
{
}

void Application::newGame()
{
	Level l;
	std::string level = utils::FileManager::readResourceFile("level.txt");
	m_board.reset(new Board(1, 1));
	l.deserialize(level, *m_board);
	mPlayer = m_board->getPlayer();
	
	mGameDrawer.reset(new draw::GameDrawer(m_board));
}
