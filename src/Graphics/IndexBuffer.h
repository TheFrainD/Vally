#pragma once

#include "Base.h"

namespace Vally
{

	class IndexBuffer
	{
	public:
		explicit IndexBuffer(const U32* indices, U32 count) noexcept;
		~IndexBuffer();

		IndexBuffer(IndexBuffer&& other) noexcept;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept;

		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;

		void Bind() const noexcept;

		void SetData(const U32* indices, U32 count) noexcept;

		[[nodiscard]] U32 GetCount() const noexcept;

		static void Unbind() noexcept;
	private:
		void Release() noexcept;

		U32 m_id = 0;
		U32 m_count = 0;
	};

}
