#pragma once
#include "Types.h"
#include "Mountain.h"
#include "Water.h"
namespace WMB
{
	class Engine
	{
	public:
		Engine() { StartUp(); }
		void StartUp();
  
  	private:
		int width = 500;
		int height = 500;

		Bitmap userBitmap;
		Bmp userBmp;

		Bmp canvas;
		Mountain m;
		Water w;

	};
}
