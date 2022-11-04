#include "IndexBuffer.h"

#include <glad/glad.h>

namespace Vally
{
	IndexBuffer::IndexBuffer(const std::span<U32>& indices) noexcept
		: m_count(indices.size())
	{
		glGenBuffers(1, &m_id);

		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, indices.size_bytes(), indices.data(), GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		if (m_id != 0)
		{
			glDeleteBuffers(1, &m_id);
		}
	}

	IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
	{
		m_id = other.m_id;
		m_count = other.m_count;

		other.m_id = 0;
		other.m_count = 0;
	}

	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
	{
		if (this != &other)
		{
			m_id = other.m_id;
			m_count = other.m_count;

			other.m_id = 0;
			other.m_count = 0;
		}

		return *this;
	}

	void IndexBuffer::Bind() const noexcept
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}

	U32 IndexBuffer::GetCount() const noexcept
	{
		return m_count;
	}

	void IndexBuffer::Unbind() noexcept
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
