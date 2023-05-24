#pragma once
#include "Types.h"
#include "Mountain.h"
namespace WMB
{
	class Engine
	{
	public:
		Engine() { StartUp(); }
		void StartUp();
	private:
		const Pixel canvasPixel = Pixel(198, 131, 39);
		int width = 500;
		int height = 500;

		Bitmap userBitmap;
		Bmp userBmp;

		std::vector<std::vector<Pixel>> canvas;
		Mountain m;

	};
}
