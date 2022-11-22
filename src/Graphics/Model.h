#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Base.h"
#include "Core/Resource.h"
#include "Graphics/Mesh.h"
#include "Graphics/Camera.h"

struct aiScene;
struct aiNode;
struct aiMesh;

namespace Vally
{
	class Model final : public Resource
	{
	public:
		VALLY_RESOURCE(Model)

		Model(std::string path, const bool flipWindingOrder = false) noexcept;

		Model(Model&& other) noexcept;
		Model& operator=(Model&& other) noexcept;

		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;

		void Scale(const glm::vec3& scale) noexcept;
		void Translate(const glm::vec3& translation) noexcept;
		void SetPosition(const glm::vec3& position) noexcept;

		void Draw() const noexcept;

		void AttachMesh(Mesh&& mesh) noexcept;

		[[nodiscard]] glm::vec3 GetPosition() const noexcept
		{
			return m_position;
		}

		[[nodiscard]] glm::vec3 GetScale() const noexcept
		{
			return m_scale;
		}

		[[nodiscard]] std::string GetPath() const noexcept
		{
			return m_path;
		}
	private:
		void LoadModel(const std::string& path, const bool flipWindingOrder = false);
		void ProcessNode(aiNode* pNode, const aiScene* pScene);
		void ProcessMesh(aiMesh* pMesh, const aiScene* pScene);

		std::string m_path;

		glm::vec3 m_position{ 0.0f };
		glm::vec3 m_scale{ 1.0f };

		std::vector<Mesh> m_meshes;
	};
}
