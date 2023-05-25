#pragma once

#include <iostream>
#include <string>
#include "../glm/glm.hpp"
#include "../bitmap/bitmap.h"

namespace WMB
{
	typedef std::string string;
	typedef std::vector <std::vector<Pixel>> Bmp;
	
	const Pixel BLACK = Pixel(0, 0, 0);

	class Location
	{
	public:
		int i;
		int j;
		Location() { i = -1; j = -1; }
		Location(int li, int lj) { i = li; j = lj; }
		
	};

	class Engine;
	class Environment;
	class Mountain;
}

