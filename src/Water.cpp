#include "Water.h"


using namespace WMB;




void Water::StartUp()
{
	std::cout << "(Water) Starting Up\n";
	Bitmap image;
	Bitmap b;

	LoadBmps(path, image, bmps);
	//std::cout << "color: " << color << "\n";

	std::cout << "(Water) Start Complete\n";
}

void Water::Draw(Bmp& userBmp, Bmp& canvas, int width, int height)
{
	std::vector<Pixel> uc;

	std::cout << "(Water) Started Drawing\n";

	DrawWaterBorder(userBmp, canvas, width, height);

	

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
				//make sure no other Mountain use these pixels
				MarkUsed(userBmp, locations);

				//draw the mountain
				DrawImage(userBmp, canvas, Location(i, j));

				//canvas[i][j] = Pixel(255, 0, 0); //Debug
			}

		}

	}
	
	std::cout << "(Water) Done Drawing\n";
}

/**
* Draw the bmp at the location on the canvas
* location should be the center of the bmp
*/
void Water::DrawImage(Bmp& userBmp, Bmp& canvas, Location location)
{
	//Get the bmp to draw
	int index = rand() % bmps.size();

	Bmp bmp = bmps[index];

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
			if (bmps[index][i][j] == BLACK)
			{

				//Location in the canvas
				Location canvasPos = BmpToCanvas(i, j, location);

				bool isValid = IsValidPos(canvasPos);
				
				//valid position
				//&& it is drawing on a water tile
				if (isValid && (userBmp[canvasPos.i][canvasPos.j] == color || userBmp[canvasPos.i][canvasPos.j] == ~color))
				{
					canvas[canvasPos.i][canvasPos.j] = BLACK;
				}
			}
		}
	}
}



/*
* Draws a line where water meets anything that is not water (aka land, mountain, etc)
*/
void Water::DrawWaterBorder(Bmp& userBmp, Bmp& canvas, int height, int width)
{
	//Is the position valid on the canvas
	auto IsValid = [&](int i, int j)
	{
		if (i < 0 || i >= height) { return false; }
		if (j < 0 || j >= width) { return false; }
		return true;
	};

	/*
	* Check the adjacent pixels to see if next to land
	* true, if next to land
	* false, if surrounded by water
	*/
	auto Check4 = [&](int i, int j)
	{	
		if (IsValid(i - 1, j)) //Above
		{
			//Not a water color
			if (userBmp[i-1][j] != color && userBmp[i-1][j] != ~color) { return true; }
		}
		if (IsValid(i + 1, j)) //Below
		{
			//Not a water color
			if (userBmp[i + 1][j] != color && userBmp[i + 1][j] != ~color) { return true; }
		}
		if (IsValid(i, j - 1)) //Left
		{
			//Not a water color
			if (userBmp[i][j-1] != color && userBmp[i][j-1] != ~color) { return true; }
		}
		if (IsValid(i, j + 1)) //Reft
		{
			//Not a water color
			if (userBmp[i][j + 1] != color && userBmp[i][j + 1] != ~color) { return true; }
		}
		return false;
	};


	//Loop through the userBmp
	for (int i = 0; i < height; i += 1)
	{
		for (int j = 0; j < width; j += 1)
		{
			//if a water pixel
			if (userBmp[i][j] == color || userBmp[i][j] == ~color)
			{
				//if next to land
				if (Check4(i, j))
				{
					canvas[i][j] = BLACK;
				}
			}

		}
	}
}