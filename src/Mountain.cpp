#include "Mountain.h"

using namespace WMB;

void Mountain::StartUp()
{
	std::cout << "made it (Mountain)\n";
	Bitmap image;

	image.open(path + "Untitled.bmp");
	
	//Test
	if (image.isImage())
	{
		std::cout << "is valid\n";
		bmps.push_back(image.toPixelMatrix());
		std::cout << "" << bmps[0].size() << "," << bmps[0][0].size();

		image.fromPixelMatrix(bmps[0]);
		image.save("assets/Mountains/TEST.bmp");
		std::cout << "done";
	}
	
}
