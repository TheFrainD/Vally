#pragma once

#include <span>

#include "Base.h"
#include "Graphics/BufferLayout.h"

namespace Vally
{
	class VertexBuffer
	{
	public:
		explicit VertexBuffer(U32 size) noexcept;
		explicit VertexBuffer(const std::span<F32>& data) noexcept;

		~VertexBuffer();

		VertexBuffer(VertexBuffer&& other) noexcept;
		VertexBuffer& operator=(VertexBuffer&& other) noexcept;

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;

		void Bind() const noexcept;

		[[nodiscard]] BufferLayout GetBufferLayout() const noexcept;
		void SetLayout(const BufferLayout& layout) noexcept;

		void SetData(const std::span<F32>& data) noexcept;

		static void Unbind() noexcept;
	private:
		U32 m_id = 0;
		BufferLayout m_layout;
	};

}
