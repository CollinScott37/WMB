#pragma once
#include "Types.h"

namespace WMB
{
	class Environment
	{
	public:
		virtual void StartUp() = 0;
		const string ppath = "assets/";
	protected:
		string path;
		Pixel color; //the pixel to look for
		std::vector<Bmp> bmps;
		int TotalPixelAmount; //total num of pixels in order to add the image 
	};
}

