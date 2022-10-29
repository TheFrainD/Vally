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

		void Update() const;
		void SwapBuffers() const;
	private:
		void Initialize();

		struct WindowData
		{
			U32 m_width{};
			U32 m_height{};
			std::string m_title;

			WindowData() = default;
		};

		GLFWwindow* m_pWindow;
		WindowData m_data;
	};
}
