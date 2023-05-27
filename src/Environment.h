#pragma once
#include "Types.h"
#include <filesystem>
namespace fs = std::filesystem;

namespace WMB
{
	class Environment
	{
	public:
		virtual void StartUp() = 0;
		const string ppath = "assets/";

		/*
		* Allow the ablity to split sting s by del
		*/
		std::vector<string> tokenize(string s, string del = " ")
		{
			std::vector<string> vs;
			int start, end = -1 * del.size();
			do {
				start = end + del.size();
				end = s.find(del, start);
				vs.push_back(s.substr(start, end - start));
			} while (end != -1);

			return vs;
		}


		/*
		* Returns the offset of the tile (based on its name)
		*/
		Offset GetOffset(string entry)
		{
			//Split string at /
			string del = "/";
			std::vector<string> test = tokenize(entry, del);
			
			//Split string at .bmp
			del = ".bmp";
			std::vector<string> test2 = tokenize(test.back(), del);

			//Split string at _
			del = "_";
			std::vector<string> test3 = tokenize(test2[0], del);

			return Offset(stoi(test3[1]), stoi(test3[2]));
		}

		//Load every tile in the path destination
		void LoadTiles(string path, Bitmap& image, std::vector<Tile>& tiles)
		{
			//Loop through all files in the path
			for (const auto& entry : fs::directory_iterator(path))
			{
			
				std::cout << entry.path() << " ";
				image.open(entry.path().string());
				
				//if it is a valid file
				if (image.isImage())
				{

					//Get Offset
					Offset o = GetOffset(entry.path().string());
					
					//Get the bmp of the tile
					Bmp bmp = image.toPixelMatrix();
					
					//Calc dimensions
					int width = bmp[0].size();
					int height = bmp.size();

					tiles.push_back(Tile(bmp, o, 0));

					std::cout << "- is valid - ";
					std::cout << "size: (" << width << ", " << height << ") Offset: (" << o.x << ", " << o.y << ")\n";
				}
				else
				{
					std::cout << "- is invalid\n";
				}
			}
		}
		
		
		virtual void Draw(Bmp& userBmp, Bmp& canvas, int width, int height) = 0;
		
		/**
		* Determines if this is a valid spot to put the Environment bmp on the canvas
		* if true, returns the locations of point on userBmp
		* if false, nothing (ish)
		*/
		bool ValidSpot(Bmp& userBmp, Bmp canvas, int ci, int cj, std::vector<Location>& locations)
		{

			int count = 0; //track number of matching colors
			int s = size / 2;

			//start at the top row of the filter
			for (int i = ci - s; i < ci + s; i += 1)
			{
				if (i < 0 || i >= userBmp.size()) { continue; } //invalid index

				//start at the left most column of the filter 
				for (int j = cj - s; j < cj + s; j += 1)
				{
					if (j < 0 || j >= userBmp[0].size()) { continue; } //invalid index


					/* //V1
					* Only counts the matching color up to size limit
					//matches the designated color
					if (userBmp[i][j] == color)
					{
						count += 1;//inc
						locations.push_back(Location(i, j)); //save location
					}

					//we don't want to any more pixels beyound the size
					if (count == size)
					{
						return true;
					}
					*/

					/*
					* V2
					* Counts every pixel that matches color
					* goes to end of filter
					*/
					/*if (userBmp[i][j] == color)
					{
						count += 1;
						locations.push_back(Location(i, j));
					}*/

					/*
					* V3
					* Counts every pixel that matches color
					* subtracts every pixel that is opposite color
					* goes to end of filter
					*/
					if (userBmp[i][j] == color)
					{
						count += 1;
						locations.push_back(Location(i, j));
					}
					else if (userBmp[i][j] == ~color)
					{
						count -= 1;
					}
				}
			}

			//part of V2 and V3
			if (count >= size)
			{
				return true;
			}

			return false;
		}
		
		/*
		* flips all colors the locations used for validation in userBmp
		*/
		void MarkUsed(Bmp& userBmp, std::vector<Location> locations)
		{
			Location l;
			for (int i = 0; i < locations.size(); i += 1)
			{
				l = locations[i];
				userBmp[l.i][l.j] = ~userBmp[l.i][l.j];
			}
		}
		
		/**
		* Draw the bmp at the location on the canvas
		* location should be the center of the bmp
		*/
		void DrawTile(Bmp& userBmp, Bmp& canvas, Location location)
		{
			//Determine which tile to draw
			int index = rand() % tiles.size();

			Bmp bmp = tiles[index].bmp;


			//Calc offset of Tile
			int xOffset = (rand() % (tiles[index].offset.x * 2 + 1)) - tiles[index].offset.x;
			int yOffset = (rand() % (tiles[index].offset.y * 2 + 1)) - tiles[index].offset.y;
			location.i += yOffset;
			location.j += xOffset;

			//Get The Bounds
			int height = bmp.size();
			int width = bmp[0].size();

			//Convert from bmp space to canvas space
			auto BmpToCanvas = [&](int i, int j, Location location)
			{
				int x = location.i + (i - height / 2);
				int y = location.j + (j - width / 2);

				return Location(x, y);
			};

			//Check if valid canvas space pos
			auto IsValidPos = [&](Location location)
			{
				if (location.i < 0 || location.i >= canvas.size()) { return false; }
				if (location.j < 0 || location.j >= canvas[0].size()) { return false; }
				return true;
			};


			//std::cout << "MADE IT HERE\n";
			//std::cout << "Center: " << location << "\n";

			//loop through the mountain bmp
			for (int i = 0; i < height; i += 1)
			{
				for (int j = 0; j < width; j += 1)
				{

					//Draw only the valid color 
					if (tiles[index].bmp[i][j] == BLACK)
					{

						//Location in the canvas
						Location canvasPos = BmpToCanvas(i, j, location);

						bool isValid = IsValidPos(canvasPos);
						if (isValid)
						{
							canvas[canvasPos.i][canvasPos.j] = BLACK;
						}
					}
				}
			}
		}

	protected:
		string path;
		Pixel color; //the pixel to look for
		std::vector<Tile> tiles;
		int size; //the size of the filter (size x size)



	};
}

