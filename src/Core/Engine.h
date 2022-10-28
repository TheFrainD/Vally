#pragma once

#include "Window.h"

namespace Vally
{
	class Engine
	{
	public:
		Engine();

		void Run();
	private:
		Window mWindow{800, 600, "Vally"};

		bool mRunning;
	};
}
