#pragma once

#include <glm/glm.hpp>

#include "Base.h"
#include "Graphics/VertexArray.h"

namespace Vally
{
	class Renderer
	{
	public:
		static void Prepare() noexcept;
		static void Clear() noexcept;
		static void SetClearColor(const glm::vec4& clearColor) noexcept;
		static void Draw(const VertexArray& vertexArray) noexcept;
		static void SetViewport(U32 x, U32 y, U32 width, U32 height);
	};
}
