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
}

