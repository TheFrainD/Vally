#pragma once

#include <string>

#include "Base.h"
#include "Event/Event.h"

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

	class WindowResizeEvent final : public Event
	{
	public:
		WindowResizeEvent(U32 width, U32 height) :
		m_width(width), m_height(height)
		{
		}

		[[nodiscard]] U32 GetWidth() const { return m_width; }

		[[nodiscard]] U32 GetHeight() const { return m_height; }

		VALLY_EVENT(WindowResizeEvent)
	private:
		U32 m_width{};
		U32 m_height{};
	};

	class WindowCloseEvent final : public Event
	{
	public:
		VALLY_EVENT(WindowCloseEvent)
	};
}
