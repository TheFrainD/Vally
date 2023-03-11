#pragma once

#include <vector>
#include <string>
#include <memory>

#include <glm/glm.hpp>

#include "Base.h"
#include "Graphics/VertexArray.h"
#include "Graphics/Material.h"

namespace Vally
{
	struct Vertex
	{
		glm::vec3 m_position{ 0.0f };
		glm::vec2 m_uv{ 0.0f };
		glm::vec3 m_normal{ 0.0f };
		glm::vec3 m_tangent{ 0.0f };

		Vertex() = default;

		Vertex(const glm::vec3& position, const glm::vec2& uv) noexcept
			: m_position(position)
			, m_uv(uv)
		{
		}

		Vertex(const glm::vec3& position, const glm::vec2& uv,
			const glm::vec3& normal) noexcept
			: m_position(position)
			, m_uv(uv)
			, m_normal(normal)
		{
		}

		Vertex(const glm::vec3& position, const glm::vec2& uv,
			const glm::vec3& normal, const glm::vec3& tangent) noexcept
			: m_position(position)
			, m_uv(uv)
			, m_normal(normal)
			, m_tangent(tangent)
		{
		}
	};

	class Mesh;


	class Mesh
	{
	public:
		explicit Mesh(std::string name = "")
			: m_name(std::move(name))
		{
		}

		~Mesh() = default;

		Mesh(Mesh&& other) noexcept;
		Mesh& operator=(Mesh&& other) noexcept;

		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		void UpdateMesh() noexcept;
		void Draw() const noexcept;

		std::vector<Vertex> m_vertices;
		std::vector<U32> m_indices;
		std::shared_ptr<Material> m_material;
	private:
		std::string m_name;
		VertexArray m_vertexArray;
	};
}
