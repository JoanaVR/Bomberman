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

		std::shared_ptr<rava::gui::Widget> SinglePlayerBtn(new rava::gui::Button("New Single Player Game", []
																		  {
																			  Application::getInstance()->closeCurrentDialog();
																			  std::cout << "SinglePlayerBtn pushed!" << std::endl; 
																			  Application::getInstance()->newGame(false);}));

		window->add(SinglePlayerBtn);

		std::shared_ptr<rava::gui::Widget> MultiPlayerBtn(new rava::gui::Button("New Multi Player Game", []
																		  {
																			  Application::getInstance()->closeCurrentDialog();
																			  std::cout << "MultiPlayerBtn pushed!" << std::endl;
																			  Application::getInstance()->newGame(true); }));

		window->add(MultiPlayerBtn);

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
