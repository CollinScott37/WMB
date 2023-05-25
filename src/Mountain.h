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
		bool ValidSpot(Bmp& userBmp, Bmp canvas, int ci, int cj, std::vector<Location>& locations);
		void MarkUsed(Bmp& userBmp, std::vector<Location> locations);
		void DrawImage(Bmp& canvas, Location location);
		Mountain()
		{
			path = ppath + "Mountains/";
			color = Pixel(194, 33, 229);
			size = 5;
		}
	};
}
