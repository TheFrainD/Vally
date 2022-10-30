#include "Engine.h"

#include "Core/Log.h"
#include "Core/Input.h"
#include "Event/EventManager.h"

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

		EventManager::Subscribe<WindowCloseEvent>(VALLY_EVENT_TCALLBACK(OnWindowClose, WindowCloseEvent));
		EventManager::Subscribe<KeyPressedEvent>(VALLY_EVENT_TCALLBACK(OnKeyPressed, KeyPressedEvent));

		while (m_running)
		{
			m_window.Update();

			m_window.SwapBuffers();
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