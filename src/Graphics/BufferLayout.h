#pragma once

#include <string>
#include <vector>

#include "Base.h"
#include "Core/Assert.h"

namespace Vally
{

	enum class BufferDataType
	{
		None,
		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool

	};

	[[nodiscard]] inline U32 BufferDataTypeSize(const BufferDataType& type) noexcept
	{
		constexpr U32 FLOAT_SIZE = 4;
		constexpr U32 INTEGER_SIZE = 4;
		constexpr U32 BOOLEAN_SIZE = 4;

		switch (type)
		{
		case BufferDataType::Float:		return FLOAT_SIZE;
		case BufferDataType::Float2:	return FLOAT_SIZE * 2;
		case BufferDataType::Float3:	return FLOAT_SIZE * 3;
		case BufferDataType::Float4:	return FLOAT_SIZE * 4;
		case BufferDataType::Int:		return INTEGER_SIZE;
		case BufferDataType::Int2:		return INTEGER_SIZE * 2;
		case BufferDataType::Int3:		return INTEGER_SIZE * 3;
		case BufferDataType::Int4:		return INTEGER_SIZE * 4;
		case BufferDataType::Bool:		return BOOLEAN_SIZE;
		}

		VALLY_ASSERT(false, "Unknow buffer data type!");
		return 0;
	}

	struct BufferElement
	{
		std::string m_name;
		BufferDataType m_type = BufferDataType::None;
		U32 m_size = 0;
		U32 m_offset = 0;
		bool m_normalized = false;

		BufferElement() noexcept = default;

		BufferElement(const BufferDataType& type, const std::string& name, bool normalized = false) noexcept;

		[[nodiscard]] U32 GetCount() const
		{
			switch (m_type)
			{
			case BufferDataType::Float:		return 1;
			case BufferDataType::Float2:	return 2;
			case BufferDataType::Float3:	return 3;
			case BufferDataType::Float4:	return 4;
			case BufferDataType::Int:		return 1;
			case BufferDataType::Int2:		return 2;
			case BufferDataType::Int3:		return 3;
			case BufferDataType::Int4:		return 4;
			case BufferDataType::Bool:		return 1;
			}

			VALLY_ASSERT(false, "Unknow buffer data type!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& elements) noexcept;

		[[nodiscard]] U32 GetStride() const noexcept;
		[[nodiscard]] const std::vector<BufferElement>& GetElements() const noexcept;
	private:
		U32 m_stride = 0;
		std::vector<BufferElement> m_elements;
	};

}
