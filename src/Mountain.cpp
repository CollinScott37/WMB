#include "Mountain.h"
using namespace WMB;

std::ostream& operator<<(std::ostream& out, Pixel const& data)
{
	return out << "(" << data.red << ", " << data.green << ", " << data.blue << ")";

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



void Mountain::Draw(Bmp& userBmp, Bmp& canvas)
{
	std::vector<Pixel> uc;
	
	std::cout << "(Mountain) Started Drawing\n";

	//std::cout << "" << userBmp[0][0];
	for (int i = 0; i < userBmp.size(); i += 1)
	{
		for (int j = 0; j < userBmp[0].size(); j += 1)
		{
			//std::cout << "" << i << ", " << j << "\n";
			
			if (uc.size() == 0)
			{
				std::cout << "0: " << userBmp[i][j] << "\n";
				uc.push_back(userBmp[i][j]);
			}
			else
			{
				bool found = false;
				for (int h = 0; h < uc.size(); h += 1)
				{
					if (uc[h] == userBmp[i][j])
					{
						found = true;
						break;
					}
				}
				if (!found)
				{
					std::cout << "1: " << userBmp[i][j] << "\n";
					uc.push_back(userBmp[i][j]);
				}
			}


			if (userBmp[i][j] == color)
			{
				std::cout << "MATCH\n";
				userBmp[i][j] = Pixel(-1,-1,-1);
				canvas[i][j].red = 0;

			}
		}
	}

	std::cout << "(Mountain) Done Drawing\n";
}

