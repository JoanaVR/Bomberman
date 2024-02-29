#include "GUI/game/game_over_screen.h"

#include <Theme.h>

#include <ModalDialog.h>
#include "Application.h"

extern int screenW ;
extern int screenH ;

namespace rava::gui {

	void GameOverDialogFactory::create(SDL_Renderer* renderer)
	{
        std::shared_ptr<rava::gui::ModalDialog> window;
        window.reset(new rava::gui::ModalDialog("Game Over"));

        std::shared_ptr<rava::gui::Widget> next(new rava::gui::Button("Next", [] { 
				std::cout << "Next pushed!" << std::endl; 
				Application::getInstance()->newGame();
				Application::getInstance()->closeCurrentDialog();
			}));
       
        window->add(next);
        window->add(std::shared_ptr<rava::gui::Label>(new rava::gui::Label("")));

		window->performLayout(renderer, { Application::getInstance()->mScreenW, Application::getInstance()->mScreenH});
        Application::getInstance()->openNewDialog(window);
	}
}



