#pragma once

#include <span>

#include "Base.h"

namespace Vally
{

	class IndexBuffer
	{
	public:
		explicit IndexBuffer(const std::span<U32>& indices) noexcept;
		~IndexBuffer();

		IndexBuffer(IndexBuffer&& other) noexcept;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept;

		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;

		void Bind() const noexcept;

		[[nodiscard]] U32 GetCount() const noexcept;

		static void Unbind() noexcept;
	private:
		U32 m_id = 0;
		U32 m_count = 0;
	};

}
