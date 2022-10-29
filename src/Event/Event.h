#pragma once

#include <string>

#define VALLY_EVENT(TYPE) [[nodiscard]] virtual EventType GetType() const override { return #TYPE; }\
	static EventType StaticType() { return #TYPE; }

namespace Vally
{
	using EventType = std::string;

	class Event
	{
	public:
		Event() = default;
		virtual ~Event() = default;

		Event(const Event&) = default;
		Event& operator=(const Event&) = default;
		Event(Event&&) = default;
		Event& operator=(Event&&) = default;

		[[nodiscard]] virtual EventType GetType() const = 0;

		[[nodiscard]] bool IsHandled() const { return m_handled; }

		void SetHandled(bool handled = true) { m_handled = handled; }
	private:
		bool m_handled = false;
	};

}
