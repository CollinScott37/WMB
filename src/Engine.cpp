#include <vector>
#include "Types.h"
#include "Engine.h"
#include "Mountain.h"

using namespace WMB;

void Engine::StartUp()
{
	m.StartUp();
	//canvas = std::vector(height, std::vector<Pixel>(width));
	std::cout << "size: " << canvas.size() << ", " << canvas[0].size() << "\n";
	Bitmap i;
	i.fromPixelMatrix(canvas);
	i.save("canvasTest.bmp");
}
