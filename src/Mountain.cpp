#include "Mountain.h"
using namespace WMB;


void Mountain::StartUp()
{
	std::cout << "(Mountain) Starting Up\n";
	Bitmap image;
	Bitmap b;

	LoadBmps(path, image, bmps);


	std::cout << "(Mountain) Start Complete\n";
	
}
