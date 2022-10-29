#pragma once

#include <string>

#include "Base.h"

struct GLFWwindow;

namespace Vally
{
	class Window
	{
	public:
		Window(U32 width, U32 height, const std::string& title);
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
			U32 Width{};
			U32 Height{};
			std::string Title;

			WindowData() = default;
		};

		GLFWwindow* mWindow;
		WindowData mData;
	};
}
