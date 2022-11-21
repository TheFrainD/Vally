#include "VertexBuffer.h"

#include <glad/glad.h>

#include "Core/Assert.h"

namespace Vally
{
	VertexBuffer::VertexBuffer(U32 size) noexcept
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

		VALLY_ASSERT(m_id != 0, "Failed to create vertex buffer!");
	}

	VertexBuffer::VertexBuffer(const void* vertices, U32 size) noexcept
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), vertices, GL_STATIC_DRAW);

		VALLY_ASSERT(m_id != 0, "Failed to create vertex buffer!");
	}

	VertexBuffer::~VertexBuffer()
	{
		Release();
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
		: m_id(other.m_id)
		, m_layout(std::move(other.m_layout))
	{
		other.m_id = 0;
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
	{
		if (this != &other)
		{
			Release();

			std::swap(m_id, other.m_id);
			std::swap(m_layout, other.m_layout);
		}

		return *this;
	}

	void VertexBuffer::Bind() const noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not bind uninitialized buffer!");
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	BufferLayout VertexBuffer::GetBufferLayout() const noexcept
	{
		return m_layout;
	}

	void VertexBuffer::SetLayout(const BufferLayout& layout) noexcept
	{
		m_layout = layout;
	}

	void VertexBuffer::SetData(const void* vertices, U32 size) noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not set data to uninitialized buffer!");

		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), vertices, GL_DYNAMIC_DRAW);
	}

	void VertexBuffer::Unbind() noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::Release() noexcept
	{
		glDeleteBuffers(1, &m_id);
		m_id = 0;
		m_layout = {};
	}
}
