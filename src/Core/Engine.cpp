#include "Engine.h"

#include "Core/Log.h"

constexpr auto WINDOW_WIDTH = 800;
constexpr auto WINDOW_HEIGHT = 600;
constexpr auto WINDOW_TITLE = "Vally";

namespace Vally
{
	Engine::Engine() :
	m_window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE),
	m_running(false)
	{
	}

	void Engine::Run()
	{
		m_running = true;

		Logger::Initialize();

		while (m_running)
		{
			Window::PollEvents();

			m_window.SwapBuffers();

			if (m_window.ShouldClose())
			{
				m_running = false;
			}
		}
	}
}
