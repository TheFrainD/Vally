#include "Mesh.h"

#include <glm/gtc/type_ptr.hpp>

#include "Graphics/Renderer.h"

namespace Vally
{
	Mesh::Mesh(Mesh&& other) noexcept
	{
		m_vertices = std::move(other.m_vertices);
		m_indices = std::move(other.m_indices);
		m_material = std::move(other.m_material);
		m_name = std::move(other.m_name);
		m_vertexArray = std::move(other.m_vertexArray);

		other.m_vertices = {};
		other.m_indices = {};
		other.m_material = {};
		other.m_name = {};
		other.m_vertexArray = {};
	}

	Mesh& Mesh::operator=(Mesh&& other) noexcept
	{
		if (this != &other)
		{
			m_vertices = std::move(other.m_vertices);
			m_indices = std::move(other.m_indices);
			m_material = std::move(other.m_material);
			m_name = std::move(other.m_name);
			m_vertexArray = std::move(other.m_vertexArray);

			other.m_vertices = {};
			other.m_indices = {};
			other.m_material = {};
			other.m_name = {};
			other.m_vertexArray = {};
		}

		return *this;
	}

	void Mesh::UpdateMesh() noexcept
	{
		if (!m_vertexArray.GetVertexBuffer())
		{
			VertexBuffer vertexBuffer(m_vertices.data(), m_vertices.size() * sizeof(Vertex));
			vertexBuffer.SetLayout(
				{
					{BufferDataType::Float3, "Position"},
					{BufferDataType::Float2, "UV"},
					{BufferDataType::Float3, "Normal"},
					{BufferDataType::Float3, "Tangent"},
				});

			m_vertexArray.SetVertexBuffer(std::move(vertexBuffer));
		}
		else
		{
			m_vertexArray.GetVertexBuffer()->SetData(m_vertices.data(), m_vertices.size() * sizeof(Vertex));
		}

		if (!m_vertexArray.GetIndexBuffer())
		{
			IndexBuffer indexBuffer(m_indices.data(), m_indices.size());
			m_vertexArray.SetIndexBuffer(std::move(indexBuffer));
		}
		else
		{
			m_vertexArray.GetIndexBuffer()->SetData(m_indices.data(), m_indices.size());
		}
	}

	void Mesh::Draw() const noexcept
	{
		m_material->Bind();
		Renderer::Draw(m_vertexArray);
	}
}
