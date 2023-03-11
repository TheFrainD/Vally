#pragma once

#include <string>
#include <span>

#include "Base.h"
#include "Core/Resource.h"

namespace Vally
{
	class Texture final : public Resource
	{
	public:
		VALLY_RESOURCE(Texture)

		explicit Texture(const std::string& filePath);

		Texture(U32 width, U32 height);

		~Texture() override;

		Texture(Texture&& other) noexcept;
		Texture& operator=(Texture&& other) noexcept;

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		void Bind(U32 slot = 0) const noexcept;

		void SetData(const std::span<U32>& data) noexcept;
	private:
		void Release() noexcept;

		U32 m_id = 0;
		U32 m_width = 0;
		U32 m_height = 0;

		std::string m_path;
	};

}
