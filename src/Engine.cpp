#include <vector>
#include "Types.h"
#include "Engine.h"
#include "Mountain.h"

using namespace WMB;

void Engine::StartUp()
{
	m.StartUp();
	
	//Load users Image
	userBitmap.open("test/sample2.bmp");
	userBmp = userBitmap.toPixelMatrix();

	//set canvas values
	height = userBmp.size();
	width = userBmp[0].size();

	//Make a canvas that has the same size as user's image and defualt color
	canvas = std::vector(height, std::vector<Pixel>(width, canvasPixel));
	
	std::cout << "size: " << width << ", " << height << "\n";
	
	m.Draw(userBmp, canvas, height, width);

	Bitmap i;
	i.fromPixelMatrix(canvas);
	i.save("canvasTest.bmp");
}
