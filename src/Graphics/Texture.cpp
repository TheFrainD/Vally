#include "Texture.h"

#include <stdexcept>

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "Vendor/stb_image.h"

#include "Core/Log.h"
#include "Core/Assert.h"

namespace Vally
{
	Texture::Texture(const std::string& filePath)
		: m_path(filePath)
	{
		I32 channels;
		I32 width;
		I32 height;

		U8* buffer = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
		if (buffer == nullptr)
		{
			throw std::runtime_error{ "Could not load image at " + m_path };
		}

		glGenTextures(1, &m_id);
		if (m_id == 0)
		{
			throw std::runtime_error{ "Could not generate OpenGL textures for " + m_path };
		}
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(buffer);
	}

	Texture::Texture(U32 width, U32 height)
	{
		glGenTextures(1, &m_id);
		if (m_id == 0)
		{
			throw std::runtime_error{ "Could not generate OpenGL textures" };
		}
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		Release();
	}

	Texture::Texture(Texture&& other) noexcept
		: m_id(other.m_id)
		, m_width(other.m_width)
		, m_height(other.m_height)
		, m_path(other.m_path)
	{
		other.m_id = 0;
		other.m_width = 0;
		other.m_height = 0;
	}

	Texture& Texture::operator=(Texture&& other) noexcept
	{
		if (this != &other)
		{
			Release();

			m_id = other.m_id;
			m_width = other.m_width;
			m_height = other.m_height;
			m_path = other.m_path;

			other.m_id = 0;
			other.m_width = 0;
			other.m_height = 0;
			m_path.clear();
		}

		return *this;
	}

	void Texture::Bind(U32 slot) const noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not bind uninitialized texture!");

		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture::SetData(const std::span<U32>& data) noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not set data to uninitialized texture!");
		VALLY_ASSERT(data.size() == m_width * m_height, "Data must cover all the texture");
		
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::Release() noexcept
	{
		glDeleteTextures(1, &m_id);
		m_id = 0;
		m_width = 0;
		m_height = 0;
	}
}
