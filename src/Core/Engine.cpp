#include "Engine.h"

#include "Core/Log.h"
#include "Core/Input.h"
#include "Event/EventManager.h"

constexpr auto WINDOW_WIDTH = 800;
constexpr auto WINDOW_HEIGHT = 600;
constexpr auto WINDOW_TITLE = "Vally";

namespace Vally
{
	Engine::Engine()
		: m_window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)
		, m_gui(m_window.GetHandle(), WINDOW_WIDTH, WINDOW_HEIGHT)
		, m_running(false)
	{
	}

	void Engine::Run()
	{
		m_running = true;

		while (m_running)
		{
			m_gui.Render();

			m_window.Update();
		}
	}

	void Engine::OnWindowClose(WindowCloseEvent& event)
	{
		m_running = false;
		event.SetHandled();
	}

	void Engine::OnKeyPressed(KeyPressedEvent& event)
	{
		if (event.GetKey() == Key::Escape)
		{
			m_running = false;
			event.SetHandled();
		}
	}
}
