#pragma once

#include "Base.h"
#include "Event.h"

namespace Vally
{
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
