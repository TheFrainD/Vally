#pragma once

#include <glm/glm.hpp>

#include "Core/Input.h"
#include "Event/Event.h"

namespace Vally
{

	class KeyEvent : public Event
	{
	public:
		explicit KeyEvent(Key key) : m_key(key)
		{
		}

		[[nodiscard]] Key GetKey() const { return m_key; }

		VALLY_EVENT(KeyEvent);
	private:
		Key m_key;
	};

	class KeyPressedEvent final : public KeyEvent
	{
	public:
		explicit KeyPressedEvent(Key key) : KeyEvent(key)
		{
		}

		VALLY_EVENT(KeyPressedEvent)
	};

	class KeyReleasedEvent final : public KeyEvent
	{
	public:
		explicit KeyReleasedEvent(Key key) : KeyEvent(key)
		{
		}

		VALLY_EVENT(KeyReleasedEvent)
	};

	class MouseMovedEvent final : public Event
	{
	public:
		MouseMovedEvent(const glm::vec2& position, const glm::vec2& previousPosition) :
		m_position(position), m_previousPosition(previousPosition)
		{
		}

		[[nodiscard]] glm::vec2 GetPosition() const { return m_position; }
		[[nodiscard]] glm::vec2 GetPreviousPosition() const { return m_previousPosition; }

		VALLY_EVENT(MouseMovedEvent)
	private:
		glm::vec2 m_position;
		glm::vec2 m_previousPosition;
	};

	class MouseScrolledEvent final : public Event
	{
	public:
		explicit MouseScrolledEvent(const glm::vec2& offset) : m_offset(offset)
		{
		}

		[[nodiscard]] glm::vec2 GetOffset() const { return m_offset; }

		VALLY_EVENT(MouseScrolledEvent)
	private:
		glm::vec2 m_offset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		explicit MouseButtonEvent(MouseButton mouseButton) : m_button(mouseButton)
		{
		}

		[[nodiscard]] MouseButton GetButton() const { return m_button; }

		VALLY_EVENT(MouseButtonEvent)
	private:
		MouseButton m_button;
	};

	class MouseButtonPressedEvent final : public MouseButtonEvent
	{
	public:
		explicit MouseButtonPressedEvent(MouseButton mouseButton) :
		MouseButtonEvent(mouseButton)
		{
		}

		VALLY_EVENT(MouseButtonPressedEvent)
	};

	class MouseButtonReleasedEvent final : public MouseButtonEvent
	{
	public:
		explicit MouseButtonReleasedEvent(MouseButton mouseButton) :
			MouseButtonEvent(mouseButton)
		{
		}

		VALLY_EVENT(MouseButtonReleasedEvent)
	};

}
