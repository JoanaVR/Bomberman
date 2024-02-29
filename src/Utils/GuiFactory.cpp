#include <vector>
#include <cmath>

#include "Utils/GuiFactory.h"
#include "FileManager.h"

extern int getDisplayDPI(float *ddpi, float *xdpi, float *ydpi);

namespace utils
{
	namespace GuiFactory
	{
		int gDisplayW = 0;
		int gDisplayH = 0;

		void init()
		{
		}

		void finalize()
		{
		}

		bool load(
			unsigned int width,
			unsigned int height)

		{

			gDisplayW = width;
			gDisplayH = height;
			return true;
		}

		const double lowDPI_Displays_Scale = 1.2;

		int getButnHight()
		{
			float ddpi, xdpi, ydpi;
			getDisplayDPI(&ddpi, &xdpi, &ydpi);

			double bthHightInCm = .9;

			return (int)(std::lround((ydpi * bthHightInCm) / 2.54));
		}

		rava::traits::Rect getNavigationRect()
		{

			double referenceHavigationRectHight = 1;

			float ddpi, xdpi, ydpi;
			getDisplayDPI(&ddpi, &xdpi, &ydpi);

			int navigationHeight = std::lround((ydpi * referenceHavigationRectHight) / 2.54);
			return {0, 0, gDisplayW, navigationHeight};
		}

		rava::traits::Rect getBoardRect()
		{
			int margin = ((gDisplayW) / (9));
			margin *= 0.2;
			int gridSize = gDisplayW - 2 * margin;
			double keypadHight = getButnHight() * 3.5;

			const int navRectHight = getNavigationRect().height();

			const int minimumEmptyspace = getButnHight() * 1.5;

			int minGridSize = (gDisplayH - navRectHight - minimumEmptyspace - keypadHight);
			if (gridSize > minGridSize)
			{
				gridSize = minGridSize;
				margin = (gDisplayW - gridSize) / 2;
			}

			int gridPlusKeepadHigh = gridSize + keypadHight;

			int top = navRectHight + (gDisplayH - navRectHight - gridPlusKeepadHigh) / 2;
			if (top < navRectHight + minimumEmptyspace)
			{
				top = navRectHight + minimumEmptyspace;
			}

			return {margin, top, margin + gridSize, top + gridSize};
		}
	}
}