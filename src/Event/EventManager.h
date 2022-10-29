#pragma once

#include <vector>
#include <map>
#include <utility>
#include <functional>

#include "Event.h"

#define VALLY_EVENT_CALLBACK(FUNC) ([this](Event& event){this->FUNC(dynamic_cast<Event&>(event));})
#define VALLY_EVENT_TCALLBACK(FUNC, TYPE) ([this](Event& event){this->FUNC(dynamic_cast<TYPE&>(event));})

namespace Vally
{

	using EventCallback = std::function<void (Event&)>;

	class EventManager
	{
	public:
		template <typename T>
		static void Subscribe(EventCallback callback)
		{
			static_assert(std::is_base_of_v<Event, T> == true, "Object must derive from Event");
			s_callbacks[T::StaticType()].push_back(callback);
		}

		template <typename T, typename ... Args>
		static void Post(Args&& ... args)
		{
			static_assert(std::is_base_of_v<Event, T> == true, "Object must derive from Event");
			T event{ std::forward<Args>(args)... };
			Event* baseEvent = &event;

			if (s_callbacks.find(baseEvent->GetType()) != s_callbacks.end())
			{
				for (auto&& callback : s_callbacks.at(baseEvent->GetType()))
				{
					if (!baseEvent->IsHandled())
					{
						callback(event);
					}
				}
			}

			baseEvent->SetHandled();
		}
	private:
		static std::map<EventType, std::vector<EventCallback>> s_callbacks;
	};

}
