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

	VertexBuffer::VertexBuffer(const std::span<F32>& data) noexcept
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(data.size_bytes()), data.data(), GL_STATIC_DRAW);

		VALLY_ASSERT(m_id != 0, "Failed to create vertex buffer!");
	}

	VertexBuffer::~VertexBuffer()
	{
		if (m_id != 0)
		{
			glDeleteBuffers(1, &m_id);
		}
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
	{
		m_id = other.m_id;
		m_layout = other.m_layout;

		other.m_id = 0;
		other.m_layout = BufferLayout();
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
	{
		if (this != &other)
		{
			m_id = other.m_id;
			m_layout = other.m_layout;

			other.m_id = 0;
			other.m_layout = BufferLayout();
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

	void VertexBuffer::SetData(const std::span<F32>& data) noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not set data to uninitialized buffer!");

		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(data.size_bytes()), data.data(), GL_DYNAMIC_DRAW);
	}

	void VertexBuffer::Unbind() noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
