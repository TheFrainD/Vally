#pragma once

#include <string>

#include "Base.h"

#define VALLY_RESOURCE(TYPE) [[nodiscard]] virtual ResourceType GetType() const noexcept override { return #TYPE; }\
	static ResourceType StaticType() noexcept { return #TYPE; }

namespace Vally
{
	using ResourceType = std::string;

	class Resource
	{
	public:
		Resource() noexcept = default;
		virtual ~Resource() = default;

		Resource(const Resource&) = delete;
		Resource& operator=(const Resource&) = delete;

		Resource(Resource&& other) = default;
		Resource& operator=(Resource&& other) = default;

		[[nodiscard]] virtual ResourceType GetType() const noexcept = 0;
	};

}