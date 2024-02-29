#pragma once

#include <DisplayScreen.h>
#include <ModalDialog.h>

#include <Label.h>
#include <Button.h>

#include <memory>

#include <iostream>

#include <SDL3/SDL.h>


namespace rava::gui {

struct GameOverDialogFactory
{
	static void create(SDL_Renderer* renderer);
};

}


