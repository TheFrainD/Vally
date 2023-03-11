#include "Framebuffer.h"

#include <glad/glad.h>

#include "Core/Assert.h"

namespace Vally
{
	Framebuffer::Framebuffer(U32 width, U32 height) noexcept
	{
		glGenFramebuffers(1, &m_id);
		VALLY_ASSERT(m_id != 0, "Failed to initialize framebuffer!");

		glGenTextures(1, &m_texture);
		glGenRenderbuffers(1, &m_depthStencilBuffer);
		VALLY_ASSERT(m_id != 0, "Failed to initialize renderbuffer!");

		glBindTexture(GL_TEXTURE_2D, m_texture);
		VALLY_ASSERT(m_id != 0, "Failed to initialize framebuffer texture!");

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		Resize(width, height);
	}

	Framebuffer::~Framebuffer()
	{
		if (m_id != 0)
		{
			glDeleteBuffers(1, &m_id);
		}

		if (m_texture != 0)
		{
			glDeleteTextures(1, &m_texture);
		}

		if (m_depthStencilBuffer != 0)
		{
			glDeleteRenderbuffers(1, &m_depthStencilBuffer);
		}
	}

	Framebuffer::Framebuffer(Framebuffer&& other) noexcept
	{
		m_id = other.m_id;
		m_texture = other.m_texture;
		m_depthStencilBuffer = other.m_depthStencilBuffer;

		other.m_id = 0;
		other.m_texture = 0;
		other.m_depthStencilBuffer = 0;
	}

	Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept
	{
		if (this != &other)
		{
			m_id = other.m_id;
			m_texture = other.m_texture;
			m_depthStencilBuffer = other.m_depthStencilBuffer;

			other.m_id = 0;
			other.m_texture = 0;
			other.m_depthStencilBuffer = 0;
		}

		return *this;
	}

	void Framebuffer::Bind() const noexcept
	{
		VALLY_ASSERT(m_id != 0 && m_depthStencilBuffer != 0 && m_texture != 0, "Can not bind uninitialized framebuffer!");
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		glViewport(0, 0, m_size.x, m_size.y);
	}

	void Framebuffer::Resize(U32 width, U32 height) noexcept
	{
		VALLY_ASSERT(m_id != 0 && m_depthStencilBuffer != 0 && m_texture != 0, "Can not resize uninitialized framebuffer!");

		m_size = { width, height };

		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, m_depthStencilBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilBuffer);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	U32 Framebuffer::GetTextureID() const noexcept
	{
		return m_texture;
	}

	glm::uvec2 Framebuffer::GetSize() const noexcept
	{
		return m_size;
	}

	void Framebuffer::Unbind() noexcept
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
