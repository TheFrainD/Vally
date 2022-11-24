#pragma once

#include <memory>
#include <string>

#include "Base.h"
#include "Graphics/Shader.h"

namespace Vally
{
	class UniformBuffer
	{
	public:
		explicit UniformBuffer(U32 size, U32 binding) noexcept;

		~UniformBuffer();

		UniformBuffer(UniformBuffer&& other) noexcept;
		UniformBuffer& operator=(UniformBuffer&& other) noexcept;

		UniformBuffer(const UniformBuffer&) = delete;
		UniformBuffer& operator=(const UniformBuffer&) = delete;

		void SetData(const void* data, U32 size, U32 offset = 0) noexcept;

		void Bind(U32 slot, const std::string& name, const std::shared_ptr<Shader>& shader) const noexcept;

		void Bind(U32 slot, const std::string& name, Shader* shader) const noexcept;
	private:
		void Release() noexcept;

		U32 m_id = 0;
	};
}
