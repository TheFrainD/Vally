#pragma once

#include "Core/Window.h"
#include "Event/WindowEvent.h"
#include "Event/InputEvent.h"

namespace Vally
{
	class Engine
	{
	public:
		Engine();

		void Run();

		void OnWindowClose(WindowCloseEvent& event);

		void OnKeyPressed(KeyPressedEvent& event);
	private:
		Window m_window;

		bool m_running;
	};
}
