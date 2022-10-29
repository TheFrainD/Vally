#include "EventManager.h"

namespace Vally
{

	std::map<EventType, std::vector<EventCallback>> EventManager::s_callbacks;

}
