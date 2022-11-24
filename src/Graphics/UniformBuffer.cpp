#include "UniformBuffer.h"

#include <glad/glad.h>

#include "Core/Assert.h"

namespace Vally
{
	UniformBuffer::UniformBuffer(U32 size, U32 binding) noexcept
	{
		glGenBuffers(1, &m_id);

		VALLY_ASSERT(m_id != 0, "Failed to create uniform buffer!");

		glBindBuffer(GL_UNIFORM_BUFFER, m_id);
		glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_id, 0, size);
	}

	UniformBuffer::~UniformBuffer()
	{
		Release();
	}

	UniformBuffer::UniformBuffer(UniformBuffer&& other) noexcept :
		m_id(other.m_id)
	{
		other.m_id = 0;
	}

	UniformBuffer& UniformBuffer::operator=(UniformBuffer&& other) noexcept
	{
		if (this != &other)
		{
			Release();

			std::swap(m_id, other.m_id);
		}

		return *this;
	}

	void UniformBuffer::SetData(const void* data, U32 size, U32 offset) noexcept
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_id);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void UniformBuffer::Bind(U32 slot, const std::string& name, const std::shared_ptr<Shader>& shader) const noexcept
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, slot, m_id);
		shader->SetUniformBlock(slot, name);
	}

	void UniformBuffer::Bind(U32 slot, const std::string& name, Shader* shader) const noexcept
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, slot, m_id);
		shader->SetUniformBlock(slot, name);
	}

	void UniformBuffer::Release() noexcept
	{
		glDeleteBuffers(1, &m_id);
		m_id = 0;
	}
}
