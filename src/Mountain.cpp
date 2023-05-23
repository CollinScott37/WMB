#include "Mountain.h"

using namespace WMB;

void Mountain::StartUp()
{
	std::cout << "made it (Mountain)\n";
	std::cout << path + "Untitled" << "\n";
	Bitmap image;
	string test = path + "Untitled.bmp";
	std::cout << test << "\n";
	string t = "assets/Mountains/Untitled.bmp";
	image.open(t);
	
	//Test
	if (image.isImage())
	{
		std::cout << "is valid\n";
		bmps.push_back(image.toPixelMatrix());
		std::cout << "" << bmps[0].size() << "," << bmps[0][0].size();
		Pixel rgb = bmps[0][0][0];
		rgb.red = 100;
		Pixel rgb2 = bmps[0][0][1];
		rgb2.green = 100;

		bmps[0][0][0] = rgb;
		bmps[0][0][1] = rgb2;
		image.fromPixelMatrix(bmps[0]);
		image.save("assets/Mountains/TEST.bmp");
		std::cout << "done";
	}
	
}
