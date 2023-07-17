#pragma once

#include <iostream>
#include <string>
#include "../glm/glm.hpp"
#include "../bitmap/bitmap.h"
#include "Location.h"



namespace WMB
{


	typedef std::string string;
	typedef std::vector <std::vector<Pixel>> Bmp;
	
	
	const Pixel canvasPixel = Pixel(198, 131, 39);

	const Pixel BLACK = Pixel(0, 0, 0);

	//How much a tile can be offsetted by
	class Offset
	{
	public:
		int x;
		int y;
		Offset() { x = 0; y = 0; }
		Offset(int xx, int yy) { x = xx; y = yy; }
	};

	//holds its bmp and size if given
	class Tile
	{
	public:
		Bmp bmp;
		Offset offset;
		int size = 0;
		Tile() { offset = Offset(); size = 0; }
		Tile(Bmp b, Offset o, int s) { bmp = b; offset = o; size = s; }
	};


	class Engine;
	class Environment;
	class Mountain;
	class Water;
	class DeepWater;
	class DeepWaterThing;

	inline double Distance(Location src, Location dest)
	{
		double y = pow(dest.i - src.i, 2);
		double x = pow(dest.j - src.j, 2);
		return sqrt(x + y);
	}

}

