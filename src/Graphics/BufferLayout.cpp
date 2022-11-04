#include "BufferLayout.h"

namespace Vally
{
	BufferElement::BufferElement(const BufferDataType& type, const std::string& name, bool normalized) noexcept
		: m_type(type), m_size(BufferDataTypeSize(type)), m_normalized(normalized)
	{
	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) noexcept
		: m_elements(elements)
	{
		for (const auto& element : m_elements)
		{
			m_stride += element.m_size;
		}
	}

	U32 BufferLayout::GetStride() const noexcept
	{
		return m_stride;
	}

	const std::vector<BufferElement>& BufferLayout::GetElements() const noexcept
	{
		return m_elements;
	}
}
