#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <optional>

#include "Core/Resource.h"
#include "Core/Assert.h"

namespace Vally
{

	class ResourceManager
	{
	public:
		ResourceManager() = delete;

		static void UnloadAll() noexcept;

		template <typename T, typename ... Args>
		static bool Load(const std::string& name, Args&& ... args) noexcept
		{
			static_assert(std::is_base_of_v<Resource, T> == true, "Object must derive from Resource");

			const std::string fullName = name + '_' + T::StaticType();

			if (Exists(fullName))
			{
				return false;
			}

			try
			{
				s_resources.insert({ fullName, std::shared_ptr<Resource>(new T(std::forward<Args>(args)...)) });
				VALLY_INFO("Loaded {} \"{}\"", T::StaticType(), name);
				return true;
			}
			catch (const std::exception& e)
			{
				VALLY_ERROR("Could not add resource \"{}\"\nError: {}", name, e.what());
			}

			return false;
		}

		template <typename T>
		static bool Load(const std::string& name, const std::shared_ptr<T> resource) noexcept
		{
			static_assert(std::is_base_of_v<Resource, T> == true, "Object must derive from Resource");

			const std::string fullName = name + '_' + T::StaticType();

			if (Exists(fullName))
			{
				return false;
			}

			s_resources.insert({ fullName, std::dynamic_pointer_cast<Resource>(resource) });
			VALLY_INFO("Loaded {} \"{}\"", T::StaticType(), name);

			return true;
		}

		static bool Exists(const std::string& name);

		template <typename T>
		static std::shared_ptr<T> Get(const std::string& name) noexcept
		{
			static_assert(std::is_base_of_v<Resource, T> == true, "Object must derive from Resource");

			const std::string fullName = name + '_' + T::StaticType();

			if (s_resources.contains(fullName))
			{
				return std::dynamic_pointer_cast<T>(s_resources.at(fullName));
			}

			return nullptr;
		}
	private:
		static std::unordered_map<std::string, std::shared_ptr<Resource>> s_resources;
	};

}