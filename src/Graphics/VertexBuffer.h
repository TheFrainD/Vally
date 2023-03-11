#pragma once

#include <glm/glm.hpp>

#include "Base.h"
#include "Graphics/BufferLayout.h"

namespace Vally
{
	class VertexBuffer
	{
	public:
		explicit VertexBuffer(U32 size) noexcept;
		explicit VertexBuffer(const void* vertices, U32 size) noexcept;

		~VertexBuffer();

		VertexBuffer(VertexBuffer&& other) noexcept;
		VertexBuffer& operator=(VertexBuffer&& other) noexcept;

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;

		void Bind() const noexcept;

		[[nodiscard]] BufferLayout GetBufferLayout() const noexcept;
		void SetLayout(const BufferLayout& layout) noexcept;

		void SetData(const void* vertices, U32 size) noexcept;

		static void Unbind() noexcept;
	private:
		void Release() noexcept;

		U32 m_id = 0;
		BufferLayout m_layout;
	};

}
