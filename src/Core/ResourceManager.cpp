#include "ResourceManager.h"

namespace Vally
{
	std::unordered_map<std::string, std::shared_ptr<Resource>> ResourceManager::s_resources;


	void ResourceManager::UnloadAll() noexcept
	{
		s_resources.clear();
	}

	bool ResourceManager::Exists(const std::string& name)
	{
		return s_resources.contains(name);
	}
}
