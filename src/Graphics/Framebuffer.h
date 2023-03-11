#pragma once

#include <glm/glm.hpp>

#include "Base.h"

namespace Vally
{

	class Framebuffer
	{
	public:
		Framebuffer(U32 width, U32 height) noexcept;
		~Framebuffer();

		Framebuffer(Framebuffer&& other) noexcept;
		Framebuffer& operator=(Framebuffer&& other) noexcept;

		Framebuffer(const Framebuffer&) = delete;
		Framebuffer& operator=(const Framebuffer&) = delete;

		void Bind() const noexcept;

		void Resize(U32 width, U32 height) noexcept;

		[[nodiscard]] U32 GetTextureID() const noexcept;

		[[nodiscard]] glm::uvec2 GetSize() const noexcept;

		static void Unbind() noexcept;
	private:
		U32 m_id = 0;
		U32 m_texture = 0;
		U32 m_depthStencilBuffer = 0;
		glm::uvec2 m_size{ 0, 0 };
	};

}
