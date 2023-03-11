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

		void Update() const noexcept;

		[[nodiscard]] GLFWwindow* GetHandle() const noexcept;

		static void SetSwapInterval(bool toggle) noexcept;
	private:
		void Initialize();

		struct WindowData
		{
			U32 m_width{};
			U32 m_height{};
			std::string m_title;
		};

		GLFWwindow* m_pWindow = nullptr;
		WindowData m_data;
	};
}
