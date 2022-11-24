#include "Renderer.h"

#include <glad/glad.h>

namespace Vally
{
	RendererSettings Renderer::s_settings;
	RendererData Renderer::s_data;
	
	void Renderer::InitData()
	{
		s_data.m_cameraBuffer = new UniformBuffer(sizeof(glm::mat4) * 2, 0);
	}

	void Renderer::DestroyData()
	{
		delete s_data.m_cameraBuffer;
	}
	
	void Renderer::Prepare() noexcept
	{
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

		if (s_settings.m_faceCulling)
		{
			glEnable(GL_CULL_FACE);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
	}

	void Renderer::Clear() noexcept
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::SetClearColor(const glm::vec4& clearColor) noexcept
	{
		glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
	}

	void Renderer::Draw(const VertexArray& vertexArray) noexcept
	{
		VALLY_ASSERT(vertexArray.GetIndexBuffer().has_value(), "Can not draw vertex array without index buffer!");
		vertexArray.Bind();
		glDrawElements(GL_TRIANGLES, vertexArray.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::SetViewport(U32 x, U32 y, U32 width, U32 height)
	{
		glViewport(x, y, width, height);
	}
}
