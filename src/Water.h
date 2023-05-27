#pragma once
#include "Environment.h"

namespace WMB
{
	class Water : public Environment
	{

	public:
		void StartUp();
		void Draw(Bmp& userBmp, Bmp& canvas, int width, int height);
		void DrawImage(Bmp& userBmp, Bmp& canvas, Location location);
		void DrawWaterBorder(Bmp& userBmp, Bmp& canvas, int height, int width);
		Water()
		{
			path = ppath + "Water/";
			color = Pixel(0,161, 255);
			size = 8;
		}
	};
}