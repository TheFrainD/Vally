#pragma once

#include "Core/Window.h"
#include "GUI/GUI.h"
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
		GUI m_gui;

		bool m_running;
	};
}
