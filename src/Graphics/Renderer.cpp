#include "Renderer.h"

#include <glad/glad.h>

namespace Vally
{
	void Renderer::Prepare() noexcept
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
		vertexArray.Bind();
		const U32 count = vertexArray.GetIndexBuffer().has_value() ? vertexArray.GetIndexBuffer()->GetCount() : 0;
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::SetViewport(U32 x, U32 y, U32 width, U32 height)
	{
		glViewport(x, y, width, height);
	}
}
