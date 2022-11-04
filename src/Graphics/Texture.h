#pragma once

#include <string>
#include <optional>
#include <span>

#include "Base.h"

namespace Vally
{

	class Texture;
	using TextureContainer = std::optional<Texture>;

	class Texture
	{
	public:
		[[nodiscard]] static TextureContainer Create(
			const std::string& name,
			const std::string& filePath) noexcept;

		[[nodiscard]] static TextureContainer Create(
			const std::string& name,
			U32 width, U32 height,
			const std::span<U32>& data) noexcept;

		~Texture();

		Texture(Texture&& other) noexcept;
		Texture& operator=(Texture&& other) noexcept;

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		void Bind(U32 slot = 0) const noexcept;

		void SetData(const std::span<U32>& data);
	private:
		Texture(std::string name, U32 id, U32 width, U32 height) noexcept;

		U32 m_id = 0;
		U32 m_width = 0;
		U32 m_height = 0;

		std::string m_name;
	};

}
