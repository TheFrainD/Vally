#include "Engine.h"

#include "Core/Log.h"

constexpr auto WINDOW_WIDTH = 800;
constexpr auto WINDOW_HEIGHT = 600;
constexpr auto WINDOW_TITLE = "Vally";

namespace Vally
{
	Engine::Engine() :
	mWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE),
	mRunning(false)
	{
	}

	void Engine::Run()
	{
		mRunning = true;

		Logger::Initialize();

		while (mRunning)
		{
			Window::PollEvents();

			mWindow.SwapBuffers();

			if (mWindow.ShouldClose())
			{
				mRunning = false;
			}
		}
	}
}
