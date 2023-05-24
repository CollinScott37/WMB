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
			//Load all mountains
			for (const auto& entry : fs::directory_iterator(path))
			{
				std::cout << entry.path() << " ";
				image.open(entry.path().string());
				if (image.isImage())
				{
					std::cout << "- is valid - ";
					bmps.push_back(image.toPixelMatrix());
					std::cout << "size: " << bmps[0].size() << "," << bmps[0][0].size() << "\n";
				}
				else
				{
					std::cout << "- is invalid\n";
				}
			}
		}
	protected:
		string path;
		Pixel color; //the pixel to look for
		std::vector<Bmp> bmps;
		int TotalPixelAmount; //total num of pixels in order to add the image 
	};
}

