#pragma once
#include "Types.h"
#include "Mountain.h"
namespace WMB
{
	class Engine
	{
	public:
		Engine() { StartUp(); }
		void StartUp();
	private:
		Mountain m;
	};
}
