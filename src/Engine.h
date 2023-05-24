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
		const int width = 500;
		const int height = 500;

		std::vector<std::vector<Pixel>> canvas = std::vector(height, std::vector<Pixel>(width, canvasPixel));
		Mountain m;

	};
}
