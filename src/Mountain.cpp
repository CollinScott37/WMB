#include "Mountain.h"
using namespace WMB;

std::ostream& operator<<(std::ostream& out, Pixel const& data)
{
	return out << "(" << data.red << ", " << data.green << ", " << data.blue << ")";
}

std::ostream& operator<<(std::ostream& out, Location const& data)
{
	return out << "(" << data.i << ", " << data.j << ")";
}

void Mountain::StartUp()
{
	std::cout << "(Mountain) Starting Up\n";
	Bitmap image;
	Bitmap b;

	LoadBmps(path, image, bmps);
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
				//make sure no other Mountain use these pixels
				MarkUsed(userBmp, locations);
				
				//draw the mountain
				DrawImage(canvas, Location(i, j));
				
				//canvas[i][j] = Pixel(255, 0, 0); //Debug
			}

		}
		
	}
	std::cout << "(Mountain) Done Drawing\n";
}



/**
* Determines if this is a valid spot to put the Environment bmp on the canvas
* if true, returns the locations of point on userBmp
* if false, nothing (ish)
*/
bool Mountain::ValidSpot(Bmp& userBmp, Bmp canvas, int ci, int cj, std::vector<Location>& locations)
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

	//part of V2 adn V3
	if (count >= size)
	{
		return true;
	}

	return false;
}

/**
* flips all colors the locations used for validation in userBmp
*/
void Mountain::MarkUsed(Bmp& userBmp, std::vector<Location> locations)
{
	Location l;
	for (int i = 0; i < locations.size(); i += 1)
	{
		l = locations[i];
		userBmp[l.i][l.j] = ~userBmp[l.i][l.j];
	}
}

/**
* Draw the Mountain at the location on the canvas
* location should be the center of the mountain bmp
*/
void Mountain::DrawImage(Bmp& canvas, Location location)
{
	//Get the bmp to draw
	int index = rand() % bmps.size();

	Bmp bmp = bmps[index];

	//Get The Bounds
	int height = bmp.size();
	int width = bmp[0].size();
	
	//Convert from bmp space to canvas space
	auto BmpToCanvas = [](int i, int j, int height, int width, Location location)
	{
		int x = location.i + (i - height / 2);
		int y = location.j + (j - width / 2);

		return Location(x, y);
	};

	//Check if valid canvas space pos
	auto IsValidPos = [](Location location, Bmp canvas)
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
				Location canvasPos = BmpToCanvas(i, j, height, width, location);
								
				bool isValid = IsValidPos(canvasPos, canvas);
				if (isValid)
				{
					canvas[canvasPos.i][canvasPos.j] = BLACK;
				}
			}
		}
	}

}

