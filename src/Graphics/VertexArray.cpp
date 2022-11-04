#include "VertexArray.h"

#include <glad/glad.h>

#include "Core/Assert.h"

namespace Vally
{
	static GLenum BufferDataTypeToOGL(const BufferDataType& type)
	{
		switch (type)
		{
		case BufferDataType::Float:		
		case BufferDataType::Float2:	
		case BufferDataType::Float3:	
		case BufferDataType::Float4:	return GL_FLOAT;
		case BufferDataType::Int:		
		case BufferDataType::Int2:		
		case BufferDataType::Int3:		
		case BufferDataType::Int4:		return GL_INT;
		case BufferDataType::Bool:		return GL_BOOL;
		}

		VALLY_ASSERT(false, "Unknow buffer data type!");
		return 0;
	}

	VertexArray::VertexArray() noexcept
	{
		glGenVertexArrays(1, &m_id);
		VALLY_ASSERT(m_id != 0, "Failed to create vertex array!");
	}

	VertexArray::~VertexArray()
	{
		if (m_id != 0)
		{
			glDeleteVertexArrays(1, &m_id);
		}
	}

	VertexArray::VertexArray(VertexArray&& other) noexcept
	{
		m_id = other.m_id;

		other.m_id = 0;
	}

	VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
	{
		if (this != &other)
		{
			m_id = other.m_id;

			other.m_id = 0;
		}

		return *this;
	}

	void VertexArray::Bind() const noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not bind uninitialized vertex array!");
		glBindVertexArray(m_id);
	}

	void VertexArray::SetVertexBuffer(const VertexBuffer& vertexBuffer) noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not set vertex buffer to uninitialized vertex array!");
		VALLY_ASSERT(vertexBuffer.GetBufferLayout().GetElements().size() != 0, "Vertex buffer has no layout!");

		glBindVertexArray(m_id);
		vertexBuffer.Bind();

		U32 vertexBufferIndex = 0;
		const auto& layout = vertexBuffer.GetBufferLayout();
		for (const auto& element : layout.GetElements())
		{
			switch (element.m_type)
			{
			case BufferDataType::Float:		
			case BufferDataType::Float2:	
			case BufferDataType::Float3:	
			case BufferDataType::Float4:
				{
					glEnableVertexAttribArray(vertexBufferIndex);
					glVertexAttribPointer(
						vertexBufferIndex,
						element.GetCount(),
						BufferDataTypeToOGL(element.m_type),
						element.m_normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						reinterpret_cast<const void*>(element.m_offset));
					vertexBufferIndex++;
					break;
				}
			case BufferDataType::Int:		
			case BufferDataType::Int2:		
			case BufferDataType::Int3:		
			case BufferDataType::Int4:
			case BufferDataType::Bool:
				{
					glEnableVertexAttribArray(vertexBufferIndex);
					glVertexAttribIPointer(
						vertexBufferIndex,
						element.GetCount(),
						BufferDataTypeToOGL(element.m_type),
						layout.GetStride(),
						reinterpret_cast<const void*>(element.m_offset));
					vertexBufferIndex++;
					break;
				}
			default:
				VALLY_ASSERT(false, "Unknow buffer data type!");
			}
		}

		glBindVertexArray(m_id);
	}

	void VertexArray::SetIndexBuffer(const IndexBuffer& indexBuffer) const noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not set index buffer to uninitialized vertex array!");
		glBindVertexArray(m_id);
		indexBuffer.Bind();
	}

	void VertexArray::Unbind() noexcept
	{
		glBindVertexArray(0);
	}
}
