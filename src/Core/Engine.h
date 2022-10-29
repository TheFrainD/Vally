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
		Window m_window;

		bool m_running;
	};
}
