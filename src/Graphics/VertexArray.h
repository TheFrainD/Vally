#pragma once

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

		void SetVertexBuffer(const VertexBuffer& vertexBuffer) noexcept;

		void SetIndexBuffer(const IndexBuffer& indexBuffer) const noexcept;

		static void Unbind() noexcept;
	private:
		U32 m_id = 0;
	};

}
