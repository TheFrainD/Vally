#pragma once

#include <string>

struct GLFWwindow;

namespace Vally
{
	class Window
	{
	public:
		Window(int width, int height, const std::string& title);
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(Window&&) = delete;

		void SwapBuffers() const;

		[[nodiscard]] bool ShouldClose() const;

		static void PollEvents();
	private:
		void Initialize();

		struct WindowData
		{
			int Width{};
			int Height{};
			std::string Title;

			WindowData() = default;
		};

		GLFWwindow* mWindow;
		WindowData mData;
	};
}
