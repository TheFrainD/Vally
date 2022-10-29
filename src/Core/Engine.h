#pragma once

#include "Core/Window.h"
#include "Event/Event.h"

namespace Vally
{
	class Engine
	{
	public:
		Engine();

		void Run();

		void OnWindowClose(WindowCloseEvent& event);
	private:
		Window m_window;

		bool m_running;
	};
}
