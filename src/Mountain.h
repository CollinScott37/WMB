#pragma once
#include "Types.h"
#include "Environment.h"


namespace WMB
{
	class Mountain : public Environment
	{
	public:
		void StartUp();
		void Draw(Bmp& userBmp, Bmp& canvas, int width, int height);
		void DrawImage(Bmp& canvas, Location location);
		Mountain()
		{
			path = ppath + "Mountains/";
			color = Pixel(194, 33, 229);
			size = 7;
		}
	};
}
