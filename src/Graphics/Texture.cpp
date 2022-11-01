#include "Texture.h"

#include <utility>

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "Vendor/stb_image.h"

#include "Core/Log.h"
#include "Core/Assert.h"

namespace Vally
{
	TextureContainer Texture::Create(const std::string& name, const std::string& filePath) noexcept
	{
		I32 channels;
		I32 width;
		I32 height;

		U8* buffer = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
		if (buffer == nullptr)
		{
			VALLY_ERROR("Could not load texture \"{}\"({})!", name, filePath);
			return {};
		}

		U32 id = 0;
		glGenTextures(1, &id);
		if (id == 0)
		{
			VALLY_ERROR("Could not generate OpenGL texture \"{}\"({})!", name, filePath);
			return {};
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Anisotropic filtering
		constexpr F32 MAX_ANISOTROPY = 16.0f;
		F32 anisotropy = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &anisotropy);

		anisotropy = (anisotropy > MAX_ANISOTROPY) ? MAX_ANISOTROPY : anisotropy;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, anisotropy);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0.0f);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(buffer);

		return Texture(name, id, width, height);
	}

	TextureContainer Texture::Create(const std::string& name, U32 width, U32 height,
		const std::span<U32>& data) noexcept
	{
		VALLY_ASSERT(data.size() == width * height, "Data must cover all the texture");

		U32 id = 0;
		glGenTextures(1, &id);
		if (id == 0)
		{
			VALLY_ERROR("Could not generate OpenGL texture \"{}\"!", name);
			return {};
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Anisotropic filtering
		constexpr F32 MAX_ANISOTROPY = 16.0f;
		F32 anisotropy = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &anisotropy);

		anisotropy = (anisotropy > MAX_ANISOTROPY) ? MAX_ANISOTROPY : anisotropy;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, anisotropy);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0.0f);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());

		glBindTexture(GL_TEXTURE_2D, 0);

		return Texture(name, id, width, height);
	}

	Texture::~Texture()
	{
		if (m_id != 0)
		{
			glDeleteTextures(1, &m_id);
			m_id = 0;
			VALLY_INFO("{} texture deleted", m_name);
		}
	}

	Texture::Texture(Texture&& other) noexcept
	{
		m_id = other.m_id;
		m_width = other.m_width;
		m_height = other.m_height;
		m_name = other.m_name;

		other.m_id = 0;
		other.m_width = 0;
		other.m_height = 0;
		other.m_name.clear();
	}

	Texture& Texture::operator=(Texture&& other) noexcept
	{
		if (this != &other)
		{
			m_id = other.m_id;
			m_width = other.m_width;
			m_height = other.m_height;
			m_name = other.m_name;

			other.m_id = 0;
			other.m_width = 0;
			other.m_height = 0;
			other.m_name.clear();
		}

		return *this;
	}

	void Texture::Bind(U32 slot) const noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not bind uninitialized texture!");

		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture::SetData(const std::span<U32>& data)
	{
		VALLY_ASSERT(m_id != 0, "Can not set data to uninitialized texture!");
		VALLY_ASSERT(data.size() == m_width * m_height, "Data must cover all the texture");
		
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::Texture(std::string name, U32 id, U32 width, U32 height) noexcept
		: m_id(id), m_width(width), m_height(height), m_name(std::move(name))
	{
		VALLY_INFO("{} texture created", m_name);
	}
}
