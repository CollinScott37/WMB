#include "Mountain.h"
using namespace WMB;

std::ostream& operator<<(std::ostream& out, Pixel const& data)
{
	return out << "(" << data.red << ", " << data.green << ", " << data.blue << ")";

}

void Mountain::StartUp()
{
	std::cout << "(Mountain) Starting Up\n";
	Bitmap image;
	Bitmap b;

	LoadBmps(path, image, bmps);


	std::cout << "(Mountain) Start Complete\n";
	
}
