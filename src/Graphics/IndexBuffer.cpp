#include "IndexBuffer.h"

#include <future>

#include <glad/glad.h>

namespace Vally
{
	IndexBuffer::IndexBuffer(const U32* indices, U32 count) noexcept
		: m_count(count)
	{
		glGenBuffers(1, &m_id);

		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(U32), indices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		Release();
	}

	IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
		: m_id(other.m_id)
		, m_count(other.m_count)
	{
		other.m_id = 0;
		other.m_count = 0;
	}

	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
	{
		if (this != &other)
		{
			Release();

			std::swap(m_id, other.m_id);
			std::swap(m_count, other.m_count);
		}

		return *this;
	}

	void IndexBuffer::Bind() const noexcept
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}

	void IndexBuffer::SetData(const U32* indices, U32 count) noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(U32), indices, GL_STATIC_DRAW);
	}

	U32 IndexBuffer::GetCount() const noexcept
	{
		return m_count;
	}

	void IndexBuffer::Unbind() noexcept
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::Release() noexcept
	{
		glDeleteBuffers(1, &m_id);
		m_id = 0;
		m_count = 0;
	}
}
