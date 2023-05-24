#include <vector>
#include "Types.h"
#include "Engine.h"
#include "Mountain.h"

using namespace WMB;

void Engine::StartUp()
{
	m.StartUp();
	
	//Load users Image
	userBitmap.open("test/sample.bmp");
	userbmp = userBitmap.toPixelMatrix();

	//set canvas values
	height = userbmp.size();
	width = userbmp[0].size();

	//Make a canvas that has the same size as user's image and defualt color
	canvas = std::vector(height, std::vector<Pixel>(width, canvasPixel));
	
	std::cout << "size: " << canvas.size() << ", " << canvas[0].size() << "\n";
	
	Bitmap i;
	i.fromPixelMatrix(canvas);
	i.save("canvasTest.bmp");
}
