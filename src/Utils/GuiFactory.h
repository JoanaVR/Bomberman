
#pragma once

#include <vector>
#include "traits.h"
#include "Utils/ResourceDefs.h"
#include <map>

namespace utils
{
	namespace GuiFactory
	{
		bool load(unsigned int screenWidth,
						 unsigned int screenHeight);
		void init();
		void finalize();

		rava::traits::Rect getNavigationRect();
		rava::traits::Rect getBoardRect();
		int getButnHight();
	}
}