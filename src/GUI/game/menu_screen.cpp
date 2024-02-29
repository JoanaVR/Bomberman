#include "menu_screen.h"

#include <Theme.h>
#include <ModalDialog.h>
#include "Application.h"


namespace rava::gui
{

	void MenuDialogFactory::create(SDL_Renderer *renderer)
	{
		std::shared_ptr<rava::gui::ModalDialog> window;
		window.reset(new rava::gui::ModalDialog("Menu"));

		std::shared_ptr<rava::gui::Widget> restartGame(new rava::gui::Button("Restart", []
																			 {
																				 std::cout << "playBtn pushed!" << std::endl;
																				 Application::getInstance()->closeCurrentDialog(); }));

		window->add(restartGame);

		window->add(std::shared_ptr<rava::gui::Label>(new rava::gui::Label("")));

		std::shared_ptr<rava::gui::Widget> CloseBtn(new rava::gui::Button("Close", []
																		  {
																			  Application::getInstance()->closeCurrentDialog();
																			  std::cout << "CloseBtn pushed!" << std::endl; }));

		window->add(CloseBtn);

		window->performLayout(renderer, {Application::getInstance()->mScreenW, Application::getInstance()->mScreenH});

		Application::getInstance()->openNewDialog(window);
	}
}
