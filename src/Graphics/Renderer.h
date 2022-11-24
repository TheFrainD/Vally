#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Base.h"
#include "Graphics/VertexArray.h"
#include "Graphics/UniformBuffer.h"

namespace Vally
{
	struct RendererSettings
	{
		bool m_faceCulling = true;
	};

	struct RendererData
	{
		UniformBuffer* m_cameraBuffer;
	};
	
	class Renderer
	{
	public:
		Renderer() = delete;

		static void InitData();
		static void DestroyData();
		static void Prepare() noexcept;
		static void Clear() noexcept;
		static void SetClearColor(const glm::vec4& clearColor) noexcept;
		static void Draw(const VertexArray& vertexArray) noexcept;
		static void SetViewport(U32 x, U32 y, U32 width, U32 height);

		static RendererSettings s_settings;
		static RendererData s_data;
	};
}
