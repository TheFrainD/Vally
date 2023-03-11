#pragma once

#include <optional>

#include "Base.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"

namespace Vally
{

	class VertexArray
	{
	public:
		VertexArray() noexcept;
		~VertexArray();

		VertexArray(VertexArray&& other) noexcept;
		VertexArray& operator=(VertexArray&& other) noexcept;

		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray& other) = delete;

		void Bind() const noexcept;

		void SetVertexBuffer(VertexBuffer&& vertexBuffer) noexcept;

		void SetIndexBuffer(IndexBuffer&& indexBuffer) noexcept;

		std::optional<VertexBuffer>& GetVertexBuffer() noexcept;

		[[nodiscard]] const std::optional<VertexBuffer>& GetVertexBuffer() const noexcept;

		std::optional<IndexBuffer>& GetIndexBuffer() noexcept;

		[[nodiscard]] const std::optional<IndexBuffer>& GetIndexBuffer() const noexcept;

		static void Unbind() noexcept;
	private:
		void Release() noexcept;

		U32 m_id = 0;
		std::optional<VertexBuffer> m_vertexBuffer;
		std::optional<IndexBuffer> m_indexBuffer;
	};

}
