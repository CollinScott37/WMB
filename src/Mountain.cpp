#include "Mountain.h"
using namespace WMB;

void Mountain::StartUp()
{
	std::cout << "(Mountain) Starting Up\n";
	Bitmap image;
	Bitmap b;

	LoadTiles(path, image, tiles);
	std::cout << "color: " << color << "\n";

	

	std::cout << "(Mountain) Start Complete\n";
	
}



void Mountain::Draw(Bmp& userBmp, Bmp& canvas, int width, int height)
{
	std::vector<Pixel> uc;
	
	std::cout << "(Mountain) Started Drawing\n";

	//Loop throught the userBmp
	for (int i = 0; i < height; i += 1)
	{
		for (int j = 0; j < width; j += 1)
		{
			
			//tracks locations used for validation
			std::vector<Location> locations;
			bool isValid = ValidSpot(userBmp, canvas, i, j, locations);
			if (isValid)
			{
				//make sure nothing else use these pixels
				MarkUsed(userBmp, locations);
				
				//draw the mountain
				DrawTile(userBmp, canvas, Location(i, j));

			}

		}
		
	}
	std::cout << "(Mountain) Done Drawing\n";
}







/**
* Draw the Mountain at the location on the canvas
* location should be the center of the mountain bmp
*/
void Mountain::DrawTile(Bmp& userBmp, Bmp& canvas, Location location)
{
	//Get the bmp to draw
	int index = rand() % tiles.size();

	int xOffset = (rand() % (tiles[index].offset.x * 2 + 1)) - tiles[index].offset.x;
	int yOffset = (rand() % (tiles[index].offset.y * 2 + 1)) - tiles[index].offset.y;
	//std::cout << "offsets: " << xOffset << ", " << yOffset << "\n";

	location.i += yOffset;
	location.j += xOffset;

	Bmp bmp = tiles[index].bmp;

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

