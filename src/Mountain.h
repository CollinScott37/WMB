#pragma once
#include "Types.h"
#include "Environment.h"


namespace WMB
{
	class Mountain : public Environment
	{
	public:
		void StartUp();
	private:
		string path = ppath + "Mountains/";
		Mountain()
		{
			path = ppath + "Mountains/";
			color = Pixel(194, 33, 229);
		}
	};
}
