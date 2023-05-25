#pragma once
#include "Types.h"
#include <filesystem>
namespace fs = std::filesystem;
namespace WMB
{
	class Environment
	{
	public:
		virtual void StartUp() = 0;
		const string ppath = "assets/";
		void LoadBmps(string path, Bitmap& image, std::vector<Bmp>& bmps)
		{
			for (const auto& entry : fs::directory_iterator(path))
			{
				std::cout << entry.path() << " ";
				image.open(entry.path().string());
				if (image.isImage())
				{
					Bmp bmp = image.toPixelMatrix();
					int width = bmp[0].size();
					int height = bmp.size();
					std::cout << "- is valid - ";
					bmps.push_back(bmp);
					std::cout << "size: " << width << "," << height << "\n";
				}
				else
				{
					std::cout << "- is invalid\n";
				}
			}
		}
		virtual void Draw(Bmp& userBmp, Bmp& canvas, int width, int height) = 0;
	protected:
		string path;
		Pixel color; //the pixel to look for
		std::vector<Bmp> bmps;
		int size; //the size of the filter (size x size)
	};
}

