#pragma once

#include <string>
#include <memory>

#include <glm/glm.hpp>

#include "Base.h"
#include "Core/Resource.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

namespace Vally
{
	struct MaterialProperties
	{
		glm::vec4 m_albedoColor{ 1.0f };
		F32 m_roughness = 0.7f;
		F32 m_metallic = 0.7f;
	};

	struct MaterialTextures
	{
		std::shared_ptr<Texture> m_albedo;
		std::shared_ptr<Texture> m_normal;
		std::shared_ptr<Texture> m_metallic;
		std::shared_ptr<Texture> m_roughness;
		std::shared_ptr<Texture> m_ao;
	};

	class Material final : public Resource
	{
	public:
		VALLY_RESOURCE(Material)

		void Bind() const noexcept;

		MaterialProperties m_properties;
		MaterialTextures m_textures;
		std::shared_ptr<Shader> m_shader;
	};
}
