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
	
		bool operator == (const Location& p)
		{
			if (i == p.i && j == p.j) { return true; }
			return false;
		}

		Location operator += (const Location l)
		{
			this->i += l.i;
			this->j += l.j;
			return *this;
		}

		Location operator /= (const int num)
		{
			this->i /= num;
			this->j /= num;
			return *this;
			//return Location(this->i / num, this->j / num);
		}

		Location operator / (const int num)
		{
			Location temp;
			temp.i = i / num;
			temp.j = j / num;
			return temp;
			//return Location(this->i / num, this->j / num);
		}

		friend std::ostream& operator<<(std::ostream& out, Location const& data)
		{
			return out << "(" << data.i << ", " << data.j << ")";
		}

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

